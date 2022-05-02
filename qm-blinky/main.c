/*.$file${.::main.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: blinky.qm
* File:  ${.::main.c}
*
* This code has been generated by QM 5.1.1 <www.state-machine.com/qm/>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*.$endhead${.::main.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpc.h"    /* QP/C framework API */
#include "bsp.h"    /* Board Support Package interface */

Q_DEFINE_THIS_FILE

/* the main function -------------------------------------------------------*/
int main() {
    static QEvt const *blinky_queueSto[10]; /* event queue buffer for Blinky */

    QF_init();  /* initialize the framework */
    BSP_init(); /* initialize the BSP */

    /* instantiate and start the Blinky active object */
    Blinky_ctor(); /* in C you must explicitly call the Blinky constructor */
    QACTIVE_START(AO_Blinky, /* active object to start */
        1U,                  /* priority of the active object */
        blinky_queueSto,     /* event queue buffer */
        Q_DIM(blinky_queueSto), /* the length of the buffer */
        (void *)0, 0U,       /* private stack (not used) */
        (QEvt *)0);          /* initialization event (not used) */

    return QF_run(); /* let the framework run the application */
}