#ifndef __LIB_EMUC_2_H__
#define __LIB_EMUC_2_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #define    MAX_COM_NUM    256
#else
  #define    MAX_COM_NUM    68
#endif

#define    VER_LEN          16
#define    CAN_NUM          2
#define    DATA_LEN         8
#define    DATA_LEN_ERR     6
#define    TIME_CHAR_NUM    13

/*-----------------------------*/
typedef struct
{
  char   fw   [VER_LEN];
  char   api  [VER_LEN];
  char   model[VER_LEN];

} VER_INFO;


/*-----------------------------*/
typedef struct
{
  int           CAN_port;
  int           flt_type;
  unsigned int  flt_id;
  unsigned int  mask;

} FILTER_INFO;


/*-----------------------------*/
typedef struct
{
  unsigned char  baud    [CAN_NUM];
  unsigned char  mode    [CAN_NUM];
  unsigned char  flt_type[CAN_NUM];
  unsigned int   flt_id  [CAN_NUM];  
  unsigned int   flt_mask[CAN_NUM];
  unsigned char  err_set;

} CFG_INFO;


/*-----------------------------*/
typedef struct
{
  int           CAN_port;
  int           id_type;
  int           rtr;
  int           dlc;
  int           msg_type;

  char          recv_time[TIME_CHAR_NUM];  /* e.g., 15:30:58:789 (h:m:s:ms) */
  unsigned int  id;
  unsigned char data     [DATA_LEN];
  unsigned char data_err [CAN_NUM][DATA_LEN_ERR];

} CAN_FRAME_INFO;


/*-----------------------------*/
typedef struct
{
  unsigned int      cnt;
  unsigned int      interval;  /* [ms] */

  CAN_FRAME_INFO   *can_frame_info;


} NON_BLOCK_INFO;



/*-----------------------------*/
typedef struct
{
  int   com_port;
  int   size_send;
  int   size_rtn;

  unsigned char send_buf[256];
  unsigned char rtn_buf [256];

} TEST_INFO;



/* for "CAN_port" */
/*-----------------------------*/
enum
{
  EMUC_CAN_1 = 0,
  EMUC_CAN_2
};


/* for "baud" */
/*-----------------------------*/
enum
{
  EMUC_BAUDRATE_100K = 4,
  EMUC_BAUDRATE_125K,
  EMUC_BAUDRATE_250K,
  EMUC_BAUDRATE_500K,
  EMUC_BAUDRATE_800K,
  EMUC_BAUDRATE_1M
};


/* for "sts" */
/*-----------------------------*/
enum
{
  EMUC_INACTIVE = 0,
  EMUC_ACTIVE
};


/* for "mode" */
/*-----------------------------*/
enum
{
  EMUC_NORMAL = 0,
  EMUC_LISTEN
};


/* for "flt_type" & id_type */
/*-----------------------------*/
enum
{
  EMUC_SID = 1,
  EMUC_EID
};


/* for "rtr" */
/*-----------------------------*/
enum
{
  EMUC_DIS_RTR = 0,
  EMUC_EN_RTR
};


/* for "err_type" */
/*-----------------------------*/
enum
{
  EMUC_DIS_ALL = 0,
  EMUC_EE_ERR,
  EMUC_BUS_ERR,
  EMUC_EN_ALL = 255
};


/* for "msg_type" */
/*-----------------------------*/
enum
{
  EMUC_DATA_TYPE = 0,
  EMUC_EEERR_TYPE,
  EMUC_BUSERR_TYPE
};



/*-------------------------------------------------------------------------------------------------------*/
#ifdef DEVELOPING_EMUC2
  int EMUCOpenDevice      (int com_port);
  int EMUCCloseDevice     (int com_port);
  int EMUCShowVer         (int com_port, VER_INFO *ver_info);
  int EMUCResetCAN        (int com_port);
  int EMUCClearFilter     (int com_port, int CAN_port);
  int EMUCInitCAN         (int com_port, int CAN1_sts,  int CAN2_sts);
  int EMUCSetBaudRate     (int com_port, int CAN1_baud, int CAN2_baud);
  int EMUCSetMode         (int com_port, int CAN1_mode, int CAN2_mode);
  int EMUCSetFilter       (int com_port, FILTER_INFO *filter_info);
  int EMUCSetErrorType    (int com_port, int err_type);
  int EMUCGetCfg          (int com_port, CFG_INFO *cfg_info);
  int EMUCExpCfg          (int com_port, const char *file_name);
  int EMUCImpCfg          (int com_port, const char *file_name);
  int EMUCSend            (int com_port, CAN_FRAME_INFO *can_frame_info);
  int EMUCReceive         (int com_port, CAN_FRAME_INFO *can_frame_info);
  int EMUCReceiveNonblock (int com_port, NON_BLOCK_INFO *non_block_info);

  #if defined(_WIN32) /* for C# */
    int EMUCReceiveNonblockCS (int com_port, unsigned int cnt, unsigned int interval, CAN_FRAME_INFO *can_frame_info);
  #endif

  /* Internal used */
  int EMUCGetCANStatus    (int com_port, int *CAN1_sts, int *CAN2_sts);
  int EMUCGetBLDID        (int com_port, unsigned char *BLD);
  int EMUCTesting         (int com_port, TEST_INFO *test_info);

#else
  #if defined(__linux__) || defined(__QNX__)
    extern int EMUCOpenDevice      (int com_port);
    extern int EMUCCloseDevice     (int com_port);
    extern int EMUCShowVer         (int com_port, VER_INFO *ver_info);
    extern int EMUCResetCAN        (int com_port);
    extern int EMUCClearFilter     (int com_port, int CAN_port);
    extern int EMUCInitCAN         (int com_port, int CAN1_sts,  int CAN2_sts);
    extern int EMUCSetBaudRate     (int com_port, int CAN1_baud, int CAN2_baud);
    extern int EMUCSetMode         (int com_port, int CAN1_mode, int CAN2_mode);
    extern int EMUCSetFilter       (int com_port, FILTER_INFO *filter_info);
    extern int EMUCSetErrorType    (int com_port, int err_type);
    extern int EMUCGetCfg          (int com_port, CFG_INFO *cfg_info);
    extern int EMUCExpCfg          (int com_port, const char *file_name);
    extern int EMUCImpCfg          (int com_port, const char *file_name);
    extern int EMUCSend            (int com_port, CAN_FRAME_INFO *can_frame_info);
    extern int EMUCReceive         (int com_port, CAN_FRAME_INFO *can_frame_info);
    extern int EMUCReceiveNonblock (int com_port, NON_BLOCK_INFO *non_block_info);
  #else
    typedef int(*EMUC_OPEN_DEVICE)      (int com_port);
    typedef int(*EMUC_CLOSE_DEVICE)     (int com_port);
    typedef int(*EMUC_SHOW_VER)         (int com_port, VER_INFO *ver_info);
    typedef int(*EMUC_RESET_CAN)        (int com_port);
    typedef int(*EMUC_CLEAR_FILTER)     (int com_port, int CAN_port);
    typedef int(*EMUC_INIT_CAN)         (int com_port, int CAN1_sts, int CAN2_sts);
    typedef int(*EMUC_SET_BAUDRATE)     (int com_port, int CAN1_baud, int CAN2_baud);
    typedef int(*EMUC_SET_MODE)         (int com_port, int CAN1_mode, int CAN2_mode);
    typedef int(*EMUC_SET_FILTER)       (int com_port, FILTER_INFO *filter_info);
    typedef int(*EMUC_SET_ERROR_TYPE)   (int com_port, int err_type);
    typedef int(*EMUC_GET_CFG)          (int com_port, CFG_INFO *cfg_info);
    typedef int(*EMUC_EXP_CFG)          (int com_port, const char *file_name);
    typedef int(*EMUC_IMP_CFG)          (int com_port, const char *file_name);
    typedef int(*EMUC_SEND)             (int com_port, CAN_FRAME_INFO *can_frame_info);
    typedef int(*EMUC_RECEIVE)          (int com_port, CAN_FRAME_INFO *can_frame_info);
    typedef int(*EMUC_RECEIVE_NON_BLOCK)(int com_port, NON_BLOCK_INFO *non_block_info);

    EMUC_OPEN_DEVICE        EMUCOpenDevice;
    EMUC_CLOSE_DEVICE       EMUCCloseDevice;
    EMUC_SHOW_VER           EMUCShowVer;
    EMUC_RESET_CAN          EMUCResetCAN;
    EMUC_CLEAR_FILTER       EMUCClearFilter;
    EMUC_INIT_CAN           EMUCInitCAN;
    EMUC_SET_BAUDRATE       EMUCSetBaudRate;
    EMUC_SET_MODE           EMUCSetMode;
    EMUC_SET_FILTER         EMUCSetFilter;
    EMUC_SET_ERROR_TYPE     EMUCSetErrorType;
    EMUC_GET_CFG            EMUCGetCfg;
    EMUC_EXP_CFG            EMUCExpCfg;
    EMUC_IMP_CFG            EMUCImpCfg;
    EMUC_SEND               EMUCSend;
    EMUC_RECEIVE            EMUCReceive;
    EMUC_RECEIVE_NON_BLOCK  EMUCReceiveNonblock;
  #endif
#endif
/*-------------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif