/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 *
 * This module contains some macros for correct placement of some GUI elements.
 * I wanted to to this better, but if I won't have time before the deadline, this will stay here
 */

/* GUI BUTTONS
 * BWS = button width (inverse) scaler
 * BHS = button height (inverse) scaler
 */
#define BWS (1.0 / 3.0) // must be between 0 and 1
#define BHS (1.0 / 5.0) // must be between 0 and 1

/* GUI SAMLPLE ITEMS
 * SB  = sample background scaler
 * SBS = sample background size
 * SBX = sample background x
 * TSBY = top sample background y
 * BSBY = bottom sample background y
 */
#define SB (9.0 / 10.0) // must be between 0 and 1
#define SBS(mW) ((mW) * SB)

#define SBX(mW) ((mW) * (1 - SB) / 2.0)
/* mw * bhs +                   // button width
 * mw * (1 - 2 * bws) / 1.5 +   // two button paddings (top and bot)
 * mw * 2 * sb +                // two sample backgrounds
 * mw * (1 - sb) / 2 +          // one sample background padding
 *
 * mw * bhs + mw * (1 - 2 * bws) / 1.5 + mw * 2 * sb + mw * (1 - sb) / 2
 * mw * (bhs + (1 - 2 * bws) / 1.5 + 2 * sb + (1 - sb) / 2)
 * mw * (bhs + (1 - 2 * bws) / 1.5 + (3 * sb + 1) / 2)
 */
#define TSBY(mW, mH) ((mH) - (mW) * (BHS + (1 - 2 * BWS) / 1.5 + (3 * SB + 1) / 2))
/* mw * bhs +                   // button width
 * mw * (1 - 2 * bws) / 1.5 +   // two button paddings (top and bot)
 * mw * sb +                    // one sample background
 *
 * mw * bhs + mw * (1 - 2 * bws) / 1.5 + mw * sb
 * mw * (bhs + (1 - 2 * bws) / 1.5 + sb)
 */
#define BSBY(mW, mH) ((mH) - (mW) * (BHS + (1 - 2 * BWS) / 1.5 + SB))
#define TOP_SAMPLE_BACKGROUND_RECT(mW, mH) QRectF(SBX(mW), TSBY(mW, mH), SBS(mW), SBS(mW))
#define BOT_SAMPLE_BACKGROUND_RECT(mW, mH) QRectF(SBX(mW), BSBY(mW, mH), SBS(mW), SBS(mW))
