/*
 * Copyright (c) Bridgetek Pte Ltd
 *
 * THIS SOFTWARE IS PROVIDED BY BRIDGETEK PTE LTD "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * BRIDGETEK PTE LTD BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * BRIDGETEK DRIVERS MAY BE USED ONLY IN CONJUNCTION WITH PRODUCTS BASED ON BRIDGETEK PARTS.
 *
 * BRIDGETEK DRIVERS MAY BE DISTRIBUTED IN ANY FORM AS LONG AS LICENSE INFORMATION IS NOT MODIFIED.
 *
 * IF A CUSTOM VENDOR ID AND/OR PRODUCT ID OR DESCRIPTION STRING ARE USED, IT IS THE
 * RESPONSIBILITY OF THE PRODUCT MANUFACTURER TO MAINTAIN ANY CHANGES AND SUBSEQUENT WHQL
 * RE-CERTIFICATION AS A RESULT OF MAKING THESE CHANGES.
 *
 * Abstract: Application to demonstrate function of EVE.
 * Author : Bridgetek
 *
 * Revision History:
 * 1.0 - date 2018.07.30 - Initial for BT816
 */

#include "Common.h"
#include "App.h"
#include "DemoUnicodeRuntime.h"

static Ft_Gpu_HalInit_t halInit;
static EVE_HalContext ph, *phost;

static void mainLoop() {
	// read and store calibration setting
#if !defined(EVE_PLATFORM_BT8XXEMU) && GET_CALIBRATION == 1
	Esd_Calibrate(phost);
	Calibration_Save(phost);
#endif

	EVE_Util_clearScreen(phost);

	while (TRUE) {
		DemoUnicodeRuntime(phost);
		
		EVE_Util_clearScreen(phost);

		EVE_Hal_close(phost);
		EVE_Hal_release();

		/* Init HW Hal for next loop*/
		Gpu_Init(phost, &halInit);
#if !defined(EVE_PLATFORM_BT8XXEMU) && GET_CALIBRATION == 1
		Calibration_Restore(phost);
#endif
	}
}

#if defined(MSVC_PLATFORM) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM) || defined(EVE_PLATFORM_BT8XXEMU)
int32_t main(int32_t argc, char8_t *argv[])
#endif
#if defined(ARDUINO_PLATFORM)
void EVE_emuMain(int argc, char *argv[])
#endif
{
	phost = &ph;
	Gpu_Init(phost, &halInit);
	mainLoop();

#if defined(MSVC_PLATFORM) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	return 0;
#endif
}
