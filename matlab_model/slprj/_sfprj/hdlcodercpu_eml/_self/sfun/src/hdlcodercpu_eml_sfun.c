/* Include files */

#include "hdlcodercpu_eml_sfun.h"
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
real_T _sfTime_;

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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2929382539U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(333816544U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(86867749U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2632579100U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2554882588U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2607695874U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1943657928U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3644472904U);
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1461027429U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3651853000U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2323421235U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(512376388U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3288050698U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3346416297U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1328181411U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1243728982U);
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
  if (nrhs<2 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern mxArray *sf_c1_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c1_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 2:
      {
        extern mxArray *sf_c2_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c2_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 3:
      {
        extern mxArray *sf_c3_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c3_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 4:
      {
        extern mxArray *sf_c4_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c4_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 5:
      {
        extern mxArray *sf_c5_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c5_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 6:
      {
        extern mxArray *sf_c6_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c6_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 7:
      {
        extern mxArray *sf_c7_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c7_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 8:
      {
        extern mxArray *sf_c8_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c8_hdlcodercpu_eml_get_autoinheritance_info();
        break;
      }

     case 9:
      {
        extern mxArray *sf_c9_hdlcodercpu_eml_get_autoinheritance_info(void);
        plhs[0] = sf_c9_hdlcodercpu_eml_get_autoinheritance_info();
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

void hdlcodercpu_eml_debug_initialize(void)
{
  _hdlcodercpu_emlMachineNumber_ = sf_debug_initialize_machine("hdlcodercpu_eml",
    "sfun",0,9,0,0,0);
  sf_debug_set_machine_event_thresholds(_hdlcodercpu_emlMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_hdlcodercpu_emlMachineNumber_,0);
}

void hdlcodercpu_eml_register_exported_symbols(SimStruct* S)
{
}
