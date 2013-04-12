/* iScissor.cpp */
/* Main file for implementing project 1.  See TO BE DONE statments below 
 * (see also correlation.cpp and iScissor.h for additional TODOs) */

#include <assert.h>

#include "correlation.h"
#include "iScissor.h"
#include "PriorityQueue.h"

// two inlined routines that may help;

inline Node &NODE(Node *n, int i, int j, int width)
{ return *(n+j*width+i); }

inline unsigned char PIXEL(const unsigned char *p, int i, int j, int c, int width)
{ return *(p+3*(j*width+i)+c); }

/************************ TO BE DONE 1 ***************************
 *InitNodeBuf
 *	INPUT: 
 *		img:	a RGB image of size imgWidth by imgHeight;
 *		nodes:	a allocated buffer of Nodes of the same size, one node corresponds to a pixel in img;
 *  OUPUT:
 *      initializes the column, row, and linkCost fields of each node in the node buffer.  
 */

void InitNodeBuf(Node *nodes, const unsigned char *img, int imgWidth, int imgHeight)
{
	double tempRslt[3 * imgWidth * imgHeight];
	double DR;
	double DG;
	double DB;
	double Dlink;
	double maxD = -1;
	//u,x,c,i-width, v,y,r,j-height

	for (int linknumber = 0; linknumber <= 7; linknumber++){
		image_filter(tempRslt, img, 0, imgWidth, imgHeight, kernels[linknumber], 3, 3, 1, 0);
		for (int x = 0; x < imgWidth; x++){
			for (int y = 0; y < imgHeight; y++){
				DR = tempRslt[3*(y*imgWidth+x)]; //DR
				DG = tempRslt[3*(y*imgWidth+x)+1]; //DG
				DB = tempRslt[3*(y*imgWidth+x)+2]; //DB
				Dlink = sqrt((DR*DR + DG*DG + DB*DB)/3);
				if (Dlink > maxD){
					maxD = Dlink;
				}
				nodes[y*imgWidth+x].linkCost[linknumber] = Dlink;
				nodes[y*imgWidth+x].column = x;
				nodes[y*imgWidth+x].row = y;
			}
		}
	}
	printf("After first loop\n");

	//At this point all of the Dlinks should be filled and maxD should be established
	for (int x = 0; x < imgWidth; x++){
		for (int y = 0; y < imgHeight; y++){
			//Link 0
			Dlink = nodes[y*imgWidth+x].linkCost[0];
			nodes[y*imgWidth+x].linkCost[0] = (maxD - Dlink);
			//Link 1
			Dlink = nodes[y*imgWidth+x].linkCost[1];
			nodes[y*imgWidth+x].linkCost[1] = (maxD - Dlink) * SQRT2;
			//Link 2
			Dlink = nodes[y*imgWidth+x].linkCost[2];
			nodes[y*imgWidth+x].linkCost[2] = (maxD - Dlink);
			//Link 3
			Dlink = nodes[y*imgWidth+x].linkCost[3];
			nodes[y*imgWidth+x].linkCost[3] = (maxD - Dlink) * SQRT2;
			//Link 4
			Dlink = nodes[y*imgWidth+x].linkCost[4];
			nodes[y*imgWidth+x].linkCost[4] = (maxD - Dlink);
			//Link 5
			Dlink = nodes[y*imgWidth+x].linkCost[5];
			nodes[y*imgWidth+x].linkCost[5] = (maxD - Dlink) * SQRT2;
			//Link 6
			Dlink = nodes[y*imgWidth+x].linkCost[6];
			nodes[y*imgWidth+x].linkCost[6] = (maxD - Dlink);
			//Link 7
			Dlink = nodes[y*imgWidth+x].linkCost[7];
			nodes[y*imgWidth+x].linkCost[7] = (maxD - Dlink) * SQRT2;
		}
	}

	printf("Node buffer filled!\n");

}
/************************ END OF TBD 1 ***************************/

/************************ TO BE DONE 4 ***************************
 *LiveWireDP:
 *	INPUT:
 *		seedX, seedY:	seed position in nodes
 *		nodes:			node buffer of size width by height;
 *      width, height:  dimensions of the node buffer;
 *		selection:		if selection != NULL, search path only in the subset of nodes[j*width+i] if selection[j*width+i] = 1;
 *						otherwise, search in the whole set of nodes. 
 *		numExpanded:		compute the only the first numExpanded number of nodes; (for debugging)
 *	OUTPUT:
 *		computes the minimum path tree from the seed node, by assigning 
 *		the prevNode field of each node to its predecessor along the minimum 
 *		cost path from the seed to that node.
 */

void LiveWireDP(int seedX, int seedY, Node *nodes, int width, int height, const unsigned char *selection, int numExpanded)
{
	//Initialize the priority queue
	CTypedPtrHeap<Node> pq;
	Node* q;
	Node* r;
	int qc, qr;
	int expanded = 0;

	//Initialize each node to INITIAL
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			nodes[y*width+x].state = INITIAL;
		}
	}

	Node *seed = nodes + (seedY*width+seedX);
	seed->totalCost = 0;
	seed->prevNode = NULL;
	pq.Insert(seed);

	while (!(pq.IsEmpty()) && (expanded < numExpanded)){
		q = pq.ExtractMin();
		expanded++;
		q->state = EXPANDED;

		qc = q->column;
		qr = q->row;
		//u,x,c,i-width, v,y,r,j-height
		//for each neighbor r of q
		//printf("Q: ROW: %d COL: %d\n",qr,qc);

		if ((qr*width + qc) >= (width*height)){
			break;
		}

		//Link 0
		if (qc < width - 1){
			r = nodes + (qr)*width+(qc+1);
			//printf("R0: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr)*width+(qc+1)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[0];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[0]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[0];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
		//Link 1
		if ((qc < width - 1) && (qr != 0)){
			r = nodes + (qr-1)*width+(qc+1);
			//printf("R1: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr-1)*width+(qc+1)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[1];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[1]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[1];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
		//Link 2
		if (qr != 0){
			r = nodes + (qr-1)*width+(qc);
			//printf("R2: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr-1)*width+(qc)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[2];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[2]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[2];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
		//Link 3
		if ((qc != 0) && (qr != 0)){
			r = nodes + (qr-1)*width+(qc-1);
			//printf("R3: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr-1)*width+(qc-1)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[3];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[3]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[3];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
		//Link 4
		if (qc != 0){
			r = nodes + (qr)*width+(qc-1);
			//printf("R4: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr)*width+(qc-1)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[4];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[4]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[4];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
		//Link 5
		if ((qc != 0) && (qr < height - 1)){
			r = nodes + (qr+1)*width+(qc-1);
			//printf("R5: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr+1)*width+(qc-1)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[5];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[5]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[5];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
		//Link 6
		if (qr < height - 1){
			r = nodes + (qr+1)*width+(qc);
			//printf("R6: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr+1)*width+(qc)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[6];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[6]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[6];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
		//Link 7
		if ((qr < height - 1)&&(qc < width - 1)){
			r = nodes + (qr+1)*width+(qc+1);
			//printf("R7: ROW: %d COL: %d\n",r->row,r->column);
			if ((selection == 0) || (selection[(qr+1)*width+(qc+1)] == 1)){
				if (r->state != EXPANDED){
					if (r->state == INITIAL){
						r->totalCost = q->totalCost + q->linkCost[7];
						r->state = ACTIVE;
						r->prevNode = q;
						pq.Insert(r);
					}
					else if (r->state == ACTIVE){
						if ((q->totalCost + q->linkCost[7]) < r->totalCost){
							r->totalCost = q->totalCost + q->linkCost[7];
							r->prevNode = q;
							pq.Update(r);
						}
					}
				}
			}
		}
	}


}
/************************ END OF TBD 4 ***************************/

/************************ TO BE DONE 5 ***************************
 *MinimumPath:
 *	INPUT:
 *		nodes:				a node buffer of size width by height;
 *		width, height:		dimensions of the node buffer;
 *		freePtX, freePtY:	an input node position;
 *	OUTPUT:
 *		insert a list of nodes along the minimum cost path from the seed node to the input node.  
 *		Notice that the seed node in the buffer has a NULL predecessor.
 *		And you want to insert a *pointer* to the Node in the path, e.g., 
 *		insert nodes+j*width+i (or &(nodes[j*width+i])) if you want to insert node at (i,j), instead of nodes[nodes+j*width+i]!!!
 *		after the procedure, the seed should be the head of path and the input code should be the tail
 */

void MinimumPath(CTypedPtrDblList <Node> *path, int freePtX, int freePtY, Node *nodes, int width, int height)
{
	Node* current = nodes + freePtY*width+freePtX;
	while (current->prevNode != NULL){
		path->AddHead(current);
		current = current->prevNode;
	}
}
/************************ END OF TBD 5 ***************************/

/************************ An Extra Credit Item *******************
 *SeeSnap:
 *	INPUT:
 *		img:				a RGB image buffer of size width by height;
 *		width, height:		dimensions of the image buffer;
 *		x,y:				an input seed position;
 *	OUTPUT:
 *		update the value of x,y to the closest edge based on local image information.
 */

void SeedSnap(int &x, int &y, unsigned char *img, int width, int height)
{
	printf("SeedSnap in iScissor.cpp: to be implemented for extra credit!\n");
}

//generate a cost graph from original image and node buffer with all the link costs;
void MakeCostGraph(unsigned char *costGraph, const Node *nodes, const unsigned char *img, int imgWidth, int imgHeight)
{
	int graphWidth = imgWidth * 3;
	int graphHeight = imgHeight * 3;
	int dgX = 3;
	int dgY = 3*graphWidth;

	int i,j;
	for (j=0;j<imgHeight;j++)
	{
		for (i=0;i<imgWidth;i++)
		{
			int nodeIndex = j*imgWidth+i;
			int imgIndex = 3*nodeIndex;
			int costIndex = 3*((3*j+1)*graphWidth+(3*i+1));
			
			const Node *node = nodes+nodeIndex;
			const unsigned char *pxl = img + imgIndex;
			unsigned char *cst = costGraph + costIndex;

			cst[0] = pxl[0];
			cst[1] = pxl[1];
			cst[2] = pxl[2];
			
			//r,g,b channels are grad info in seperate channels;				
			DigitizeCost(cst	   + dgX, node->linkCost[0]);
			DigitizeCost(cst - dgY + dgX, node->linkCost[1]);
			DigitizeCost(cst - dgY      , node->linkCost[2]);
			DigitizeCost(cst - dgY - dgX, node->linkCost[3]);
			DigitizeCost(cst	   - dgX, node->linkCost[4]);
			DigitizeCost(cst + dgY - dgX, node->linkCost[5]);
			DigitizeCost(cst + dgY	   ,  node->linkCost[6]);
			DigitizeCost(cst + dgY + dgX, node->linkCost[7]);
		}
	}
}
