#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

int main() {
	Display *disp;
	XRRScreenResources *screen;
	XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;
	int iscres;
	int icrtc;
        int i;

	disp = XOpenDisplay(0);
	int rate;
	screen = XRRGetScreenResources (disp, DefaultRootWindow(disp));
	XRRScreenConfiguration *sc = XRRGetScreenInfo(disp, DefaultRootWindow(disp));


        printf("######### ncrtc: %d. \n", screen->ncrtc);
        for (i = 0; i < screen->ncrtc; i++) {
            RRCrtc  crtc = screen->crtcs[i];
            printf("%lu, \n", crtc);
            crtc_info = XRRGetCrtcInfo(disp, screen, crtc);
            printf("\t x:%d, y:%d .\n", crtc_info->x, crtc_info->y);
            printf("\t width: %d, height: %d. \n", crtc_info->width, crtc_info->height);
            printf("\t npossible: %d. \n", crtc_info->npossible);
            XRRFreeCrtcInfo(crtc_info);
        }

        printf("######### noutput: %d. \n", screen->noutput);
        for (i = 0; i < screen->noutput; i++) {
            RROutput output = screen->outputs[i];
            printf("%lu \n", output); 


            info = XRRGetOutputInfo(disp, screen, output);
            printf("--------------------------------------------------");
            printf("info->connection: %d---------. \n", info->connection);
            printf("info->name: %s --------------. \n", info->name);


            printf(" crtc count : %d. \n", info->ncrtc);
            for (int j = 0; j < info->ncrtc; j++) {
                 crtc_info = XRRGetCrtcInfo(disp, screen, info->crtcs[j]);
                 printf("\t\t x:%d, y:%d .\n", crtc_info->x, crtc_info->y);
                 printf("\t\t width: %d, height: %d. \n", crtc_info->width, crtc_info->height);
                 printf("\t\t npossible: %d. \n", crtc_info->npossible);
                 XRRFreeCrtcInfo(crtc_info);
            }
            XRRFreeOutputInfo (info);
        }

       printf("######### nmode: %d. \n", screen->nmode);
       for (i = 0; i < screen->nmode; i++) {
           XRRModeInfo mode = screen->modes[i];
           printf("------------------------.\n");
           printf(" id: %lu----------------.\n", mode.id);
           printf(" width: %d -------------.\n", mode.width);
           printf(" height: %d ------------.\n", mode.height);
           printf(" name:  %s -------------.\n", mode.name);
           printf(" name length: %d -------.\n\n", mode.nameLength);
       }
        
	//for (iscres = screen->noutput; iscres > 0; ) {
	//	--iscres;

	//	info = XRRGetOutputInfo (disp, screen, screen->outputs[iscres]);
	//	if (info->connection == RR_Connected) {
	//		for (icrtc = info->ncrtc; icrtc > 0;) {
	//			--icrtc;

	//			crtc_info = XRRGetCrtcInfo (disp, screen, screen->crtcs[icrtc]);
	//			fprintf(stderr, "==> %dx%d+%dx%d\n", crtc_info->x, crtc_info->y, crtc_info->width, crtc_info->height);
	//			XRRFreeCrtcInfo(crtc_info);
	//		}
	//	}
	//	XRRFreeOutputInfo (info);
	//}
	rate = XRRConfigCurrentRate(sc);
	printf("rate = %d\n", rate);
	XRRFreeScreenResources(screen);

	return 0;
}
