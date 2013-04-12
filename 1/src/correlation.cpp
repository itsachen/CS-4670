#include "correlation.h"

/************************ TO BE DONE 2 **************************/
/*
 *	INPUT: 
 *		origImg:		the original image, 
 *		imgWidth:		the width of the image
 *		imgHeight:		the height of the image
 *						the image is arranged such that 
 *						origImg[3*(row*imgWidth+column)+0], 
 *						origImg[3*(row*imgWidth+column)+1], 
 *						origImg[3*(row*imgWidth+column)+2]
 *						are R, G, B values for pixel at (column, row).
 *
 *      kernel:			the 2D filter kernel,
 *		knlWidth:		the width of the kernel
 *		knlHeight:		the height of the kernel
 *		
 *		scale, offset:  after correlating the kernel with the origImg, 
 *						each pixel should be divided by scale and then added by offset
 *      
 *		selection:      a byte array of the same size as the image, 
 *						indicating where in the original image should be filtered, e.g., 
 *						selection[k] == 1 ==> pixel k should be filtered
 *                      selection[k] == 0 ==> pixel k should NOT be filtered
 *                      a special case is selection is a NULL pointer, which means all the pixels should be filtered. 
 *
 *  OUTPUT:
 *		rsltImg:		the filtered image of the same size as original image.
 *						it is a valid pointer ( allocated already ).
 */

void image_filter(double *rsltImg, const unsigned char *origImg, const unsigned char *selection, 
			int imgWidth, int imgHeight, 
			const double *kernel, int knlWidth, int knlHeight,
			double scale, double offset)
{
  //u,x is col-width, v,y is row-height
  //x and y increase to the lower right

  double rsltPixel[3];

  for (int x = 0; x < imgWidth; x++){
    for (int y = 0; y < imgHeight; y++){
      if ((selection == 0) || (selection[3*(y*imgWidth+x)] == 1)){
        pixel_filter(rsltPixel, x, y, origImg, imgWidth, imgHeight, kernel, knlWidth, knlHeight, scale, offset);
        //printf("Real:%f Fake:%f\n",rsltImg[3*(x*imgWidth+y)],rsltPixel[0]);
        rsltImg[3*(y*imgWidth+x)] = rsltPixel[0];
        rsltImg[3*(y*imgWidth+x)+1] = rsltPixel[1];
        rsltImg[3*(y*imgWidth+x)+2] = rsltPixel[2];
      }
    }
  }
}

/************************ END OF TBD 2 **************************/


/************************ TO BE DONE 3 **************************/
/*
 *	INPUT: 
 *      x:				a column index,
 *      y:				a row index,
 *		origImg:		the original image, 
 *		imgWidth:		the width of the image
 *		imgHeight:		the height of the image
 *						the image is arranged such that 
 *						origImg[3*(row*imgWidth+column)+0], 
 *						origImg[3*(row*imgWidth+column)+1], 
 *						origImg[3*(row*imgWidth+column)+2]
 *						are R, G, B values for pixel at (column, row).
 *
 *      kernel:			the 2D filter kernel,
 *		knlWidth:		the width of the kernel
 *		knlHeight:		the height of the kernel
 *
 *		scale, offset:  after correlating the kernel with the origImg, 
 *						the result pixel should be divided by scale and then added by offset
 *
 *  OUTPUT:
 *		rsltPixel[0], rsltPixel[1], rsltPixel[2]:		
 *						the filtered pixel R, G, B values at row y , column x;
 */

void pixel_filter(double rsltPixel[3], int x, int y, const unsigned char *origImg, int imgWidth, int imgHeight, 
			  const double *kernel, int knlWidth, int knlHeight,
			  double scale, double offset)
{	
  memset(rsltPixel,0,sizeof(double)*3); //rsltPixel is zeroed every time
  //printf("Original:\nR:%d\nG:%d\nB:%d\n",origImg[3*(y*imgWidth+x)],origImg[3*(y*imgWidth+x)+1],origImg[3*(y*imgWidth+x)+2]);
  int kernel_offset = ((knlWidth - 1)/2);
  //u,x is col, v,y is row
  if (!((x == 0) ||(y == 0) || (x == imgWidth - 1) || (y == imgWidth - 1))){
    for (int u = -(kernel_offset); u <= kernel_offset; u++){
      for (int v = -(kernel_offset); v <= kernel_offset; v++){
        //R
        rsltPixel[0] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+0];
        //G
        rsltPixel[1] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+1];
        //B
        rsltPixel[2] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+2];
      }
    }
  }
  else if ((x == 0) && (y == 0)){
    for (int u = 0; u <= kernel_offset; u++){
      for (int v = 0; v <= kernel_offset; v++){
        //R
        rsltPixel[0] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+0];
        //G
        rsltPixel[1] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+1];
        //B
        rsltPixel[2] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+2];
      }
    }
  }
  else if (x == 0){
    for (int u = 0; u <= kernel_offset; u++){
      for (int v = -(kernel_offset); v <= kernel_offset; v++){
        //R
        rsltPixel[0] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+0];
        //G
        rsltPixel[1] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+1];
        //B
        rsltPixel[2] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+2];
      }
    }
  }
  else if (y == 0){
    for (int u = -(kernel_offset); u <= kernel_offset; u++){
      for (int v = 0; v <= kernel_offset; v++){
        //R
        rsltPixel[0] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+0];
        //G
        rsltPixel[1] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+1];
        //B
        rsltPixel[2] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+2];
      }
    }
  }
  else if ((x == imgWidth - 1) && (y == imgWidth - 1)){
    for (int u = -(kernel_offset); u <= 0; u++){
      for (int v = -(kernel_offset); v <= 0; v++){
        //R
        rsltPixel[0] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+0];
        //G
        rsltPixel[1] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+1];
        //B
        rsltPixel[2] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+2];
      }
    }
  }
  else if (x == imgWidth - 1){
    for (int u = -(kernel_offset); u <= 0; u++){
      for (int v = -(kernel_offset); v <= kernel_offset; v++){
        //R
        rsltPixel[0] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+0];
        //G
        rsltPixel[1] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+1];
        //B
        rsltPixel[2] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+2];
      }
    }
  }
  else if (y == imgWidth - 1){
    for (int u = -(kernel_offset); u <= kernel_offset; u++){
      for (int v = -(kernel_offset); v <= 0; v++){
        //R
        rsltPixel[0] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+0];
        //G
        rsltPixel[1] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+1];
        //B
        rsltPixel[2] += kernel[(v + kernel_offset)*knlWidth+(u + kernel_offset)] * origImg[3*((y+v)*imgWidth+(x+u))+2];
      }
    }
  }

  rsltPixel[0] = rsltPixel[0]/scale + offset;
  rsltPixel[1] = rsltPixel[1]/scale + offset;
  rsltPixel[2] = rsltPixel[2]/scale + offset;
  //printf("After:\nR:%f\nG:%f\nB:%f\n\n",rsltPixel[0],rsltPixel[1],rsltPixel[2]);
}

/************************ END OF TBD 3 **************************/

