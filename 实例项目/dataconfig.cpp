#include "dataconfig.h"
#include <QDebug>
dataConfig::dataConfig()
{

}

void dataConfig::init(int level){
    qDebug() << level;
    if (array1 != nullptr)
        delete[] array1;
    switch (level) {
    case  1:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 2:{
        array1= new int[4*4] {    /* 放堆上 */
                0,1,1,1,
                1,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 3:{
        array1= new int[4*4] {    /* 放堆上 */
                1,0,1,1,
                1,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 4:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,0,1,
                1,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 5:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,0,
                1,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 6:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                0,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 7:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 8:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,0,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 9:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,1,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 10:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,0,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 11:{array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                0,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 12:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,1,0,0,
                1,1,0,1
        };
        break;
    }
    case 13:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,1,0,
                1,1,0,1
        };

        break;
    }
    case 14:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,1,
                1,1,0,1
        };

        break;
    }
    case 15:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                1,1,0,1
        };
        break;
    }
    case 16:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                0,1,0,1
        };
        break;
    }
    case 17:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                1,0,0,1
        };
        break;
    }
    case 18:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                1,1,1,1
        };
        break;
    }
    case 19:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                1,1,0,0
        };
        break;
    }
    case 20:{
        array1= new int[4*4] {    /* 放堆上 */
                1,1,1,1,
                1,1,0,1,
                1,0,0,0,
                0,0,1,1
        };
        break;
    }
//    default:{
//         array1= new int[4*4] {    /* 放堆上 */
//                1,1,1,1,
//                1,1,0,1,
//                1,0,0,0,
//                1,1,0,1
//        };
//        break;
//    }
    }
}


