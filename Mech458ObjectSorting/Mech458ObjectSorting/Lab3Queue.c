///* Solution Set for the LinkedQueue.c */
///*
    //Course		: UVic Mechatronics 458
    //Milestone	: 3
    //Title		: Data structures for MCUs and the Linked Queue Library
//
    //Name 1:	Clifton Tollefson	Student ID: V01004341
    //Name 2:	Khephren Gould		Student ID: V01012827
//
    //Description: You can change the following after you read it.  Lab3 Demo
//
    //This main routine will only serve as a testing routine for now. At some point you can comment out
    //The main routine, and can use the following library of functions in your other applications
//
    //To do this...make sure both the .C file and the .H file are in the same directory as the .C file
    //with the MAIN routine (this will make it more convenient)
//*/
//
///* include libraries */
//#include <stdlib.h>
//#include <avr/io.h>
//#include "LinkedQueue.h" /* This is the attached header file, which cleans things up */
                         ///* Make sure you read it!!! */
///* global variables */
///* Avoid using these */
//#define WAIT_MS (20)
//#define DEBOUNCE (20)
//void display(link **head, link **tail);
//// A blocking timer implementation that uses the TIM1 peripheral
//void mTimer(uint16_t count)
//{
    //uint16_t i = 0;
    //// set the timer clock prescaler to 8
    //TCCR1B |= _BV(CS11);
    //// wavegen mode 11 automatically clears count after OCR1A is reached
    //TCCR1B |= _BV(WGM12);
    //// sets the output compare register to 1003
    //OCR1A = 0x03EB;
    //// clear the count register
    //TCNT1 = 0x0000;
    //// enable output compare interrupts
    //TIMSK1 |= 0x02;
    //// clear the output compare interrupt flag
    //TIFR1 = _BV(OCF1A);
    //while (i < count)
    //{
        //// check for output compare interrupt flag
        //if ((TIFR1 & 0x02) == 0x02)
        //{
            //// clear the output compare interrupt flag
            //TIFR1 = _BV(OCF1A);
            //// 1ms has passed, increment the count
            //i++;
        //}
    //}
    //// shut off the timer
    //TCCR1B &= ~_BV(CS11);
    //return;
//}
//
///* main routine
   //You need to add the mtimer function to this project.    */
//
//int main()
//{
//
    //link *head;    /* The ptr to the head of the queue */
    //link *tail;    /* The ptr to the tail of the queue */
//
    //DDRC = 0xFF; /* Used for debugging purposes only LEDs on PORTC */
    //DDRA = 0x00; /* Set direction of Pin A to be used as an input*/
//
    //setup(&head, &tail);
    //while (1)
    //{
        //while ((PINA & 0x4) != 0)
            //;
		////debounce
		//mTimer(DEBOUNCE);
        //uint8_t input = PINA & 0x3;
        //button_handler(input, &head, &tail);
    //}
//
    //return (0);
//} /* main */
//
///**************************************************************************************/
///***************************** SUBROUTINES ********************************************/
///**************************************************************************************/
//
//// handler function for when the button is pressed
//void button_handler(char input, link **head, link **tail)
//{
    //mTimer(20);
    //link *newLink;
    //link *oldLink;
    //int list_size = size(head, tail);
    //if (list_size < 3)
    //{
//
        //// first 3 inputs: Create new link and store the value in the element
        //initLink(&newLink);
        //newLink->e.itemCode = (PINA &= 0x3); // masks input to only first two bits
        //enqueue(head, tail, &newLink);
    //}
    //else
    //{
        //// this is the 4th input: Remove from front of queue and add new item to end of queue
        //dequeue(head, &oldLink);
        //initLink(&newLink);
        //newLink->e.itemCode = (PINA &= 0x3); // masks input to only first two bits
        //enqueue(head, tail, &newLink);
        //display(head, tail);
    //}
//} // button_hander
//
//void display(link **head, link **tail)
//{
    //link *temp = *head;
    //PORTC |= temp->e.itemCode & 0x3;
    //temp = temp->next;
    //mTimer(WAIT_MS);
    //PORTC |= ((temp->e.itemCode & 0x3) << 2);
    //temp = temp->next;
    //mTimer(WAIT_MS);
    //PORTC |= ((temp->e.itemCode & 0x3) << 4);
    //temp = temp->next;
    //mTimer(WAIT_MS);
    //// clear elements for next iteration
    //clearQueue(head, tail);
	//while((PINA & 0x4) != 0);
	//// clear previous output
	//PORTC = 0;
//} // display
//
///**************************************************************************************
 //* DESC: initializes the linked queue to 'NULL' status
 //* INPUT: the head and tail pointers by reference
 //*/
//
//void setup(link **h, link **t)
//{
    //*h = NULL; /* Point the head to NOTHING (NULL) */
    //*t = NULL; /* Point the tail to NOTHING (NULL) */
    //return;
//} /*setup*/
//
///**************************************************************************************
 //* DESC: This initializes a link and returns the pointer to the new link or NULL if error
 //* INPUT: the head and tail pointers by reference
 //*/
//void initLink(link **newLink)
//{
    //// link *l;
    //*newLink = malloc(sizeof(link));
    //(*newLink)->next = NULL;
    //return;
//} /*initLink*/
//
///****************************************************************************************
 //*  DESC: Accepts as input a new link by reference, and assigns the head and tail
 //*  of the queue accordingly
 //*  INPUT: the head and tail pointers, and a pointer to the new link that was created
 //*/
///* will put an item at the tail of the queue */
//void enqueue(link **h, link **t, link **nL)
//{
//
    //if (*t != NULL)
    //{
        ///* Not an empty queue */
        //(*t)->next = *nL;
        //*t = *nL; //(*t)->next;
    //} /*if*/
    //else
    //{
        ///* It's an empty Queue */
        ////(*h)->next = *nL;
        //// should be this
        //*h = *nL;
        //*t = *nL;
    //} /* else */
    //return;
//} /*enqueue*/
//
///**************************************************************************************
 //* DESC : Removes the link from the head of the list and assigns it to deQueuedLink
 //* INPUT: The head and tail pointers, and a ptr 'deQueuedLink'
 //* 		 which the removed link will be assigned to
 //*/
///* This will remove the link and element within the link from the head of the queue */
//void dequeue(link **h, link **deQueuedLink)
//{
    ///* ENTER YOUR CODE HERE */
    //*deQueuedLink = *h; // Will set to NULL if Head points to NULL
    ///* Ensure it is not an empty queue */
    //if (*h != NULL)
    //{
        //*h = (*h)->next;
    //} /*if*/
//
    //return;
//} /*dequeue*/
//
///**************************************************************************************
 //* DESC: Peeks at the first element in the list
 //* INPUT: The head pointer
 //* RETURNS: The element contained within the queue
 //*/
///* This simply allows you to peek at the head element of the queue and returns a NULL pointer if empty */
//element firstValue(link **h)
//{
    //return ((*h)->e);
//} /*firstValue*/
//
///**************************************************************************************
 //* DESC: deallocates (frees) all the memory consumed by the Queue
 //* INPUT: the pointers to the head and the tail
 //*/
///* This clears the queue */
//void clearQueue(link **h, link **t)
//{
//
    //link *temp;
//
    //while (*h != NULL)
    //{
        //temp = *h;
        //*h = (*h)->next;
        //free(temp);
    //} /*while*/
//
    ///* Last but not least set the tail to NULL */
    //*t = NULL;
//
    //return;
//} /*clearQueue*/
//
///**************************************************************************************
 //* DESC: Checks to see whether the queue is empty or not
 //* INPUT: The head pointer
 //* RETURNS: 1:if the queue is empty, and 0:if the queue is NOT empty
 //*/
///* Check to see if the queue is empty */
//char isEmpty(link **h)
//{
    ///* ENTER YOUR CODE HERE */
    //return (*h == NULL);
//} /*isEmpty*/
//
///**************************************************************************************
 //* DESC: Obtains the number of links in the queue
 //* INPUT: The head and tail pointer
 //* RETURNS: An integer with the number of links in the queue
 //*/
///* returns the size of the queue*/
//int size(link **h, link **t)
//{
//
    //link *temp; /* will store the link while traversing the queue */
    //int numElements;
//
    //numElements = 0;
//
    //temp = *h; /* point to the first item in the list */
//
    //while (temp != NULL)
    //{
        //numElements++;
        //temp = temp->next;
    //} /*while*/
//
    //return (numElements);
//} /*size*/
