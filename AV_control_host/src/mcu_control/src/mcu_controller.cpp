/**
 * @file mcu_controller.cpp
 * 
 * @author Bingchuan Wei (weibc19@mails.tsinghua.edu.cn)
 * This controller is written to collect the data from logi steering_wheel, manupilate them
 * and send them to the stm32 via CAN
 * @version 0.1
 * @date 2021-04-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */


//how to use a dynamic lib in my package
// The relationship between package and msgs

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Joy.h>
#include "mcu_control/lib_emuc_2.h"

static int find_emuc (void);
static void print_data (CAN_FRAME_INFO frame_info);

/*Global Variables For CAN*/
int             com_port;
int             CAN_port;
const char     *file_name = "emuc_config";
int    rtn;//state varible 
unsigned char   data_send[DATA_LEN];

VER_INFO         ver_info;
CFG_INFO         cfg_info;
FILTER_INFO      filter_info;
CAN_FRAME_INFO   frame_send;
CAN_FRAME_INFO   frame_recv;
NON_BLOCK_INFO   non_block_info;


/* pthread */
pthread_t    TRD_recv = 0;
static void *TRD_recv_fx (void *ptr);


/* API library from EMUC*/
extern char *comports [MAX_COM_NUM];

int const ANG_MAX = 3600;
int const THR_MAX = 1000;//360 and 1000 for the limits of steering wheel and throttle

void testCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  //Used to be binded with the overloaded function
}
void testCallback(const sensor_msgs::Joy::ConstPtr msg,int16_t& ang,int16_t& throttle)
{
  ang = (msg->axes[0]+1) * ANG_MAX;
  throttle = (msg->axes[2]+1) /2 * THR_MAX;
  ROS_INFO("Throttle is  %d",  throttle);
}

void Encode(uint8_t CAN_buffer[],const int16_t ang,const int16_t throttle,uint8_t serial_num)
{
    CAN_buffer[0] = serial_num;
    CAN_buffer[1] = throttle >> 8;
    CAN_buffer[2] = throttle & 0xff;
    CAN_buffer[3] = ang >> 8;
    CAN_buffer[4] = ang & 0xff;
}


int  CAN_Init()
{

    com_port = find_emuc();
    if(com_port == -1)
    {    
        printf("No EMUC device !\n");
        return 1;
    }
      /* ----- EMUCOpenDevice() ----- */
    rtn = EMUCOpenDevice(com_port);
    if(rtn)
    {
        printf("Open %s failed !\n", comports[com_port]);
        return 1;
    }
    else
    {
        printf("Open %s successfully !\n", comports[com_port]);
        printf("==============================================\n");
    }
      /* ----- EMUCInitCAN() ----- */
    rtn = EMUCInitCAN(com_port, EMUC_INACTIVE, EMUC_INACTIVE);
    if(rtn)
        printf("EMUC initial CAN failed !\n");
    else
    {
        printf("EMUC initial CAN successfully !\n");
        printf("==============================================\n");
    }
      /* ----- EMUCShowVer() ----- */
    rtn = EMUCShowVer(com_port, &ver_info);
    if(rtn)
        printf("EMUC show version failed !\n");
    else
    {    
        printf("EMUC show version successfully !\n");
        printf("FW ver: %s\n",  ver_info.fw);
        printf("LIB ver: %s\n", ver_info.api);
        printf("Model: %s\n",   ver_info.model);
        printf("==============================================\n");
    }
    /* ----- EMUCResetCAN() ----- */
    rtn = EMUCResetCAN(com_port);
    if(rtn)
        printf("EMUC reset CAN failed !\n");
    else
    {
        printf("EMUC reset CAN successfully !\n");
        printf("==============================================\n");
    }
    /* ----- EMUCClearFilter() ----- */
    CAN_port = EMUC_CAN_1;
    rtn = EMUCClearFilter(com_port, CAN_port);
    if(rtn)
        printf("EMUC clear filter failed !\n");
    else
    {
        printf("EMUC clear filter successfully !\n");
        printf("==============================================\n");
    }

    /* ----- EMUCSetBaudRate() ----- */
    rtn = EMUCSetBaudRate(com_port, EMUC_BAUDRATE_1M, EMUC_BAUDRATE_1M);
    if(rtn)
        printf("EMUC set baud rate failed !\n");
    else
    {
        printf("EMUC set baud rate successfully! Baud Rate: 1MHz!\n");
        printf("==============================================\n");
    }


    /* ----- EMUCSetErrorType() ----- */
    rtn = EMUCSetErrorType(com_port, EMUC_DIS_ALL);
    if(rtn)
        printf("EMUC set error type failed !\n");
    else
    {
        printf("EMUC set error type successfully !\n");
        printf("==============================================\n");
    }
    /* ----- EMUCSetMode() ----- */
    rtn = EMUCSetMode(com_port, EMUC_NORMAL, EMUC_NORMAL);
    if(rtn)
        printf("EMUC set mode failed !\n");
    else
    {
        printf("EMUC set mode successfully ! Mode: NORMAL\n");
        printf("==============================================\n");
    }


      /* ----- EMUCSetFilter() ----- */
    filter_info.CAN_port = EMUC_CAN_1;
    filter_info.flt_type = EMUC_EID;
    filter_info.flt_id   = 0;
    filter_info.flt_id   = 0;
    filter_info.mask     = 0;

    rtn = EMUCSetFilter(com_port, &filter_info);
    if(rtn)
        printf("EMUC set CAN 1 filter failed !\n");
    else
    {
        printf("EMUC set CAN 1 filter successfully !All Frames accepted\n");
        printf("==============================================\n");
    }

    filter_info.CAN_port = EMUC_CAN_2;
    filter_info.flt_type = EMUC_EID;
    filter_info.flt_id   = 0;
    filter_info.mask     = 0;

    rtn = EMUCSetFilter(com_port, &filter_info);
    if(rtn)
        printf("EMUC set CAN 2 filter failed !\n");
    else
    {
        printf("EMUC set CAN 2 filter successfully !All frames accepted\n");
        printf("==============================================\n");
    }

      /* ----- EMUCGetCfg() ----- */
    rtn = EMUCGetCfg(com_port, &cfg_info);
    if(rtn)
        printf("EMUC get config. failed !\n");
    else
    {
        printf("EMUC get config. successfully !\n");
        for(int i=0; i<CAN_NUM; i++)
        {
        printf("----------------------------------------------\n");
        printf("CAN %d:\n", i+1);
        printf("baud rate = %d\n", cfg_info.baud[i]);
        printf("mode = %d\n", cfg_info.mode[i]);
        printf("filter type = %d\n", cfg_info.flt_type[i]);
        printf("filter id = %08X\n", cfg_info.flt_id[i]);
        printf("filter mask = %08X\n", cfg_info.flt_mask[i]);

        }
        printf("----------------------------------------------\n");
        printf("error set = %d\n", cfg_info.err_set);
        printf("==============================================\n");
    }

      /* Send & Receive must initial CAN to EMUC_ACTIVE */
  /*-----------------------------------------------------------------------------------------*/
  EMUCClearFilter(com_port, EMUC_CAN_1);  /* not necessary */
  EMUCClearFilter(com_port, EMUC_CAN_2);  /* not necessary */
  EMUCInitCAN    (com_port, EMUC_ACTIVE, EMUC_ACTIVE);//Very Necessary!!!!!!
}

void CAN_Send(unsigned char data_send[])
{
    memset(&frame_send, 0, sizeof(CAN_FRAME_INFO));
    frame_send.CAN_port = EMUC_CAN_1;
    frame_send.id_type  = EMUC_EID;
    frame_send.rtr      = EMUC_DIS_RTR;
    frame_send.dlc      = 8;
    frame_send.id       = 0x001234AB;
    memcpy(frame_send.data, data_send, DATA_LEN);

    for(int i=0; i<10; i++)
    {
        usleep(1);
        EMUCSend(com_port, &frame_send);
    }
}


int main(int argc, char **argv)
{
    int16_t steer_ang = 0;
    int16_t throttle = 0;
    uint8_t CAN_buffer[8];
    ros::init(argc, argv, "mcu_controller");
    CAN_Init();
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::Joy>("joy", 1000, boost::bind(&testCallback,_1,steer_ang,throttle));
    
    





        /* ----- EMUCReceiveNonblock() ----- */
    non_block_info.cnt = 5;
    non_block_info.interval = 10 * 1000;
    non_block_info.can_frame_info = (CAN_FRAME_INFO *) malloc(non_block_info.cnt * sizeof(CAN_FRAME_INFO));

    printf("Non-block receive ------> Time start !\n");
    rtn = EMUCReceiveNonblock(com_port, &non_block_info);
    if(rtn)
    {
        printf("Non-block receive ------> Time out or Data enough !\n");
        for(int i=0; i<rtn; i++)
        {
        switch (non_block_info.can_frame_info[i].msg_type)
        {
            case EMUC_DATA_TYPE:
                                    print_data(non_block_info.can_frame_info[i]);
                                    break;
            case EMUC_EEERR_TYPE:
                                    printf("EEPROM Error !\n");
                                    break;
            case EMUC_BUSERR_TYPE:
                                    printf("Bus Error !\n");

                                    printf("error data (CAN 1): ");
                                    for(int j=0; j<DATA_LEN_ERR; j++)
                                    printf("%02X ", frame_recv.data_err[EMUC_CAN_1][j]);
                                    printf("\n");

                                    printf("error data (CAN 2): ");
                                    for(int j=0; j<DATA_LEN_ERR; j++)
                                    printf("%02X ", frame_recv.data_err[EMUC_CAN_2][j]);
                                    printf("\n");

                                    break;
        }
        }
        printf("==============================================\n");
    }
    else
    {
        printf("Non-block receive ------> Time out (No data) !\n");
        printf("==============================================\n");
    }

    free(non_block_info.can_frame_info);


    /* ----- EMUCReceive() ----- */
    pthread_create(&TRD_recv, NULL, TRD_recv_fx, NULL);
    printf("EMUC reveice start ...\n");


    #if 0
    /* ----- EMUCCloseDevice() ----- */
    EMUCCloseDevice(com_port);
    #endif
    
    ros::Rate loop_rate(100);
    while(ros::ok()) {
      //x
      CAN_Send(CAN_buffer);

      ros::spinOnce();
      loop_rate.sleep();
    }

    return 0;
}

/*--------------------------------------------------------------------------------------------------------*/
static void *TRD_recv_fx (void *ptr)
{
  /* Let thread can be canceled at anytime */
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

  int    i;
  int    rtn;

  while(1)
  {
    memset(&frame_recv, 0, sizeof(CAN_FRAME_INFO));
    rtn = EMUCReceive(com_port, &frame_recv);

    if(rtn == 1)
    {
      switch (frame_recv.msg_type)
      {
        case EMUC_DATA_TYPE:
                                print_data(frame_recv);
                                break;
        case EMUC_EEERR_TYPE:
                                printf("EEPROM Error !\n");
                                break;
        case EMUC_BUSERR_TYPE:
                                printf("Bus Error !\n");
                                printf("error data (CAN 1): ");
                                for(i=0; i<DATA_LEN_ERR; i++)
                                  printf("%02X ", frame_recv.data_err[EMUC_CAN_1][i]);
                                printf("\n");

                                printf("error data (CAN 2): ");
                                for(i=0; i<DATA_LEN_ERR; i++)
                                  printf("%02X ", frame_recv.data_err[EMUC_CAN_2][i]);
                                printf("\n");
                                break;
      }
    }
  }

  pthread_exit(0);
  return NULL;

} /* END: TRD_recv_fx() */


/*--------------------------------------------------------------------------------------------------------*/
static int find_emuc (void)
{
  int  i;
  int  rtn;

  for(i=0; i<MAX_COM_NUM; i++)
  {
    rtn = EMUCOpenDevice(i);

    if(rtn == 0)
    {
      EMUCCloseDevice(i);
      return i;
    }
  }

  return -1;

} /* END: find_emuc() */



/*--------------------------------------------------------------------------------------------------------*/
static void print_data (CAN_FRAME_INFO frame_info)
{
  static unsigned long cnt_1 = 0;
  static unsigned long cnt_2 = 0;

  int i;

  /* CAN port & cnt */
  if(frame_info.CAN_port == EMUC_CAN_1)
  {
    cnt_1++;
    printf("(CAN 1) %lu. ", cnt_1);
  }
  else if(frame_info.CAN_port == EMUC_CAN_2)
  {
    cnt_2++;
    printf("(CAN 2) %lu. ", cnt_2);
  }

  /* ID */
  if(frame_info.id_type == EMUC_SID)
    printf("ID: %03X; ", frame_info.id);
  else if(frame_info.id_type == EMUC_EID)
    printf("ID: %08X; ", frame_info.id);
  
  /* Data */
  printf("Data: ");
  for(i=0; i<frame_info.dlc; i++)
    printf("%02X ", frame_info.data[i]);
  printf("\n");


} /* END: print_data() */