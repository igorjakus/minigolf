/*-
 * Copyright (c) 2005 Boris Mikhaylov
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <stdexcept>

#include "alnumbers.h"
#include "bs2b.h"

namespace {

/* Set up all data. */
void init(Bs2b::bs2b *bs2b)
{
    float Fc_lo, Fc_hi;
    float G_lo, G_hi;

    switch(bs2b->level)
    {
    case Bs2b::LowCLevel: /* Low crossfeed level */
        Fc_lo = 360.0f;
        Fc_hi = 501.0f;
        G_lo  = 0.398107170553497f;
        G_hi  = 0.205671765275719f;
        break;

    case Bs2b::MiddleCLevel: /* Middle crossfeed level */
        Fc_lo = 500.0f;
        Fc_hi = 711.0f;
        G_lo  = 0.459726988530872f;
        G_hi  = 0.228208484414988f;
        break;

    case Bs2b::HighCLevel: /* High crossfeed level (virtual speakers are closer to itself) */
        Fc_lo = 700.0f;
        Fc_hi = 1021.0f;
        G_lo  = 0.530884444230988f;
        G_hi  = 0.250105790667544f;
        break;

    case Bs2b::LowECLevel: /* Low easy crossfeed level */
        Fc_lo = 360.0f;
        Fc_hi = 494.0f;
        G_lo  = 0.316227766016838f;
        G_hi  = 0.168236228897329f;
        break;

    case Bs2b::MiddleECLevel: /* Middle easy crossfeed level */
        Fc_lo = 500.0f;
        Fc_hi = 689.0f;
        G_lo  = 0.354813389233575f;
        G_hi  = 0.187169483835901f;
        break;

    case Bs2b::HighECLevel: /* High easy crossfeed level */
    default:
        bs2b->level = Bs2b::HighECLevel;

        Fc_lo = 700.0f;
        Fc_hi = 975.0f;
        G_lo  = 0.398107170553497f;
        G_hi  = 0.205671765275719f;
        break;
    }

    float g{1.0f / (1.0f - G_hi + G_lo)};

    /* $fc = $Fc / $s;
     * $d  = 1 / 2 / pi / $fc;
     * $x  = exp(-1 / $d);
     */
    float x{      std::exp(-al::numbers::pi_v<float>*2.0f*Fc_lo/static_cast<float>(bs2b->srate))};
    bs2b->b1_lo = x;
    bs2b->a0_lo = G_lo * (1.0f - x) * g;

    x           = std::exp(-al::numbers::pi_v<float>*2.0f*Fc_hi/static_cast<float>(bs2b->srate));
    bs2b->b1_hi = x;
    bs2b->a0_hi = (1.0f - G_hi * (1.0f - x)) * g;
    bs2b->a1_hi = -x * g;
}

} // namespace

/* Exported functions.
 * See descriptions in "bs2b.h"
 */
namespace Bs2b {

void bs2b::set_params(int level_, int srate_)
{
    if(srate_ < 1)
        throw std::runtime_error{"BS2B srate < 1"};

    level = level_;
    srate = srate_;
    init(this);
}

void bs2b::clear()
{
    history.fill(bs2b::t_last_sample{});
}

void bs2b::cross_feed(float *RESTRICT Left, float *RESTRICT Right, size_t SamplesToDo)
{
    const float a0lo{a0_lo};
    const float b1lo{b1_lo};
    const float a0hi{a0_hi};
    const float a1hi{a1_hi};
    const float b1hi{b1_hi};
    std::array<std::array<float,2>,128> samples;

    for(size_t base{0};base < SamplesToDo;)
    {
        const size_t todo{std::min(samples.size(), SamplesToDo-base)};

        /* Process left input */
        float z_lo{history[0].lo};
        float z_hi{history[0].hi};
        for(size_t i{0};i < todo;i++)
        {
            const float x{Left[i]};
            float y{a0hi*x + z_hi};
            z_hi = a1hi*x + b1hi*y;
            samples[i][0] = y;

            y = a0lo*x + z_lo;
            z_lo = b1lo*y;
            samples[i][1] = y;
        }
        history[0].lo = z_lo;
        history[0].hi = z_hi;

        /* Process right input */
        z_lo = history[1].lo;
        z_hi = history[1].hi;
        for(size_t i{0};i < todo;i++)
        {
            const float x{Right[i]};
            float y{a0lo*x + z_lo};
            z_lo = b1lo*y;
            samples[i][0] += y;

            y = a0hi*x + z_hi;
            z_hi = a1hi*x + b1hi*y;
            samples[i][1] += y;
        }
        history[1].lo = z_lo;
        history[1].hi = z_hi;

        for(size_t i{0};i < todo;i++)
            *(Left++) = samples[i][0];
        for(size_t i{0};i < todo;i++)
            *(Right++) = samples[i][1];

        base += todo;
    }
}

} // namespace Bs2b
