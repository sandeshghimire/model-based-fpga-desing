/* Include files */

#include "hdlcodercpu_eml_sfun.h"
#include "hdlcodercpu_eml_sfun_debug_macros.h"
#include "c1_hdlcodercpu_eml.h"
#include "c2_hdlcodercpu_eml.h"
#include "c3_hdlcodercpu_eml.h"
#include "c4_hdlcodercpu_eml.h"
#include "c5_hdlcodercpu_eml.h"
#include "c6_hdlcodercpu_eml.h"
#include "c7_hdlcodercpu_eml.h"
#include "c8_hdlcodercpu_eml.h"
#include "c9_hdlcodercpu_eml.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _hdlcodercpu_emlMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void hdlcodercpu_eml_initializer(void)
{
}

void hdlcodercpu_eml_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_hdlcodercpu_eml_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==8) {
    c8_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==9) {
    c9_hdlcodercpu_eml_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_hdlcodercpu_eml_process_testpoint_info_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char machineName[128];
  if (nrhs < 3 || !mxIsChar(prhs[0]) || !mxIsChar(prhs[1]))
    return 0;

  /* Possible call to get testpoint info. */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_testpoint_info"))
    return 0;
  mxGetString(prhs[1], machineName, sizeof(machineName)/sizeof(char));
  machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
  if (!strcmp(machineName, "hdlcodercpu_eml")) {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
    switch (chartFileNumber) {
     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }

    return 1;
  }

  return 0;

#else

  return 0;

#endif

}

unsigned int sf_hdlcodercpu_eml_process_check_sum_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3266353362U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(856397414U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2610653956U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1017357900U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(142217122U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3189319027U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2128293193U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2379668617U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c1_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c2_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c3_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c4_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c5_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c6_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c7_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 8:
        {
          extern void sf_c8_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c8_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       case 9:
        {
          extern void sf_c9_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
          sf_c9_hdlcodercpu_eml_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2649826407U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4059492847U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4196251047U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2231188399U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1178853319U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3534321606U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2004713181U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1190779902U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hdlcodercpu_eml_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "XRngt67UQsRgZyhphRLq1F") == 0) {
          extern mxArray *sf_c1_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c1_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "iQoNdPywKovccOPWnyfr9F") == 0) {
          extern mxArray *sf_c2_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c2_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "aQZM11PfE8111SX4Y5wbOE") == 0) {
          extern mxArray *sf_c3_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c3_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "0RsUhPUxjRZzk6jM2C4iKF") == 0) {
          extern mxArray *sf_c4_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c4_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "nU9Z7PNXvB0nhKlvt3oAxB") == 0) {
          extern mxArray *sf_c5_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c5_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "qdnzeFYouBW5seSceU95lD") == 0) {
          extern mxArray *sf_c6_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c6_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "tC2MRMFezwB9sA3cHlQje") == 0) {
          extern mxArray *sf_c7_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c7_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 8:
      {
        if (strcmp(aiChksum, "z6cRnj2tzVGVOD0tqpTIkF") == 0) {
          extern mxArray *sf_c8_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c8_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 9:
      {
        if (strcmp(aiChksum, "83rHnCMl77355RYj2Yoy3G") == 0) {
          extern mxArray *sf_c9_hdlcodercpu_eml_get_autoinheritance_info(void);
          plhs[0] = sf_c9_hdlcodercpu_eml_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hdlcodercpu_eml_get_eml_resolved_functions_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray
          *sf_c1_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray
          *sf_c4_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray
          *sf_c5_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray
          *sf_c6_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray
          *sf_c7_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 8:
      {
        extern const mxArray
          *sf_c8_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c8_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 9:
      {
        extern const mxArray
          *sf_c9_hdlcodercpu_eml_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c9_hdlcodercpu_eml_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hdlcodercpu_eml_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "0Z8rTyXEYo8mUP3uRibS1C") == 0) {
          extern mxArray *sf_c1_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c1_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "kvFtfeYdN8pSp74NTHn3ZB") == 0) {
          extern mxArray *sf_c2_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c2_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "jmUNtUfDEZdekHVen4giQC") == 0) {
          extern mxArray *sf_c3_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c3_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "WpKUyZMujhavGZGBM31PU") == 0) {
          extern mxArray *sf_c4_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c4_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "4duIofkJdw6JTUxjCgz1JC") == 0) {
          extern mxArray *sf_c5_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c5_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "qMruEl8pgU9jxqTU25Y1tG") == 0) {
          extern mxArray *sf_c6_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c6_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "jSs6jtRyjbX2vuO9hqi4oE") == 0) {
          extern mxArray *sf_c7_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c7_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "UpX7fahExLArbUaLDEhkiD") == 0) {
          extern mxArray *sf_c8_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c8_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "43cgF6r42FClzmnRECa2PG") == 0) {
          extern mxArray *sf_c9_hdlcodercpu_eml_third_party_uses_info(void);
          plhs[0] = sf_c9_hdlcodercpu_eml_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_hdlcodercpu_eml_updateBuildInfo_args_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "0Z8rTyXEYo8mUP3uRibS1C") == 0) {
          extern mxArray *sf_c1_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "kvFtfeYdN8pSp74NTHn3ZB") == 0) {
          extern mxArray *sf_c2_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "jmUNtUfDEZdekHVen4giQC") == 0) {
          extern mxArray *sf_c3_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c3_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "WpKUyZMujhavGZGBM31PU") == 0) {
          extern mxArray *sf_c4_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c4_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "4duIofkJdw6JTUxjCgz1JC") == 0) {
          extern mxArray *sf_c5_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "qMruEl8pgU9jxqTU25Y1tG") == 0) {
          extern mxArray *sf_c6_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c6_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "jSs6jtRyjbX2vuO9hqi4oE") == 0) {
          extern mxArray *sf_c7_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c7_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "UpX7fahExLArbUaLDEhkiD") == 0) {
          extern mxArray *sf_c8_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c8_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "43cgF6r42FClzmnRECa2PG") == 0) {
          extern mxArray *sf_c9_hdlcodercpu_eml_updateBuildInfo_args_info(void);
          plhs[0] = sf_c9_hdlcodercpu_eml_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void hdlcodercpu_eml_debug_initialize(struct SfDebugInstanceStruct*
  debugInstance)
{
  _hdlcodercpu_emlMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "hdlcodercpu_eml","sfun",0,9,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _hdlcodercpu_emlMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _hdlcodercpu_emlMachineNumber_,0);
}

void hdlcodercpu_eml_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_hdlcodercpu_eml_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("hdlcodercpu_eml",
      "hdlcodercpu_eml");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_hdlcodercpu_eml_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
