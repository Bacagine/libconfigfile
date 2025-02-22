#include <errno.h>
#include "conf.h"

typedef struct STRUCT_GLOBAL_PRM {
  char szLogDir[260];
  char szDebugLevel[16];
  bool bLogOnTerminal;
  char szLanguage[8];
} STRUCT_GLOBAL_PRM, *PSTRUCT_GLOBAL_PRM;

STRUCT_GLOBAL_PRM gstGlobalPrm;

STRUCT_CONF_FILE astConfFile[] = {
  { "LogDir"       , gstGlobalPrm.szLogDir        , sizeof(gstGlobalPrm.szLogDir)       , DATATYPE_STRING, "./log" },
  { "DebugLevel"   , gstGlobalPrm.szDebugLevel    , sizeof(gstGlobalPrm.szDebugLevel)   , DATATYPE_STRING, "0"     },
  { "LogOnTerminal", &gstGlobalPrm.bLogOnTerminal , sizeof(gstGlobalPrm.bLogOnTerminal) , DATATYPE_BOOL  , "false" },
  { "Language"     , &gstGlobalPrm.szLanguage     , sizeof(gstGlobalPrm.szLanguage)     , DATATYPE_STRING, "EN_USA"},
// NOTE: NULL indicates the end of array. NEVER REMOVE IT!!!
  { NULL           , NULL                         , 0                                   , DATATYPE_NULL  , NULL    }
};

int main(int argc, char *argv[]) {
  if ( !bReadConfFile("test.conf", astConfFile) ) {
    fprintf(stderr, "E: Error reading file [test.conf]: %s!", strerror(errno));
    return -1;
  }

  printf(
    "LogDir.......: [%s]\n"
    "DebugLevel...: [%s]\n"
    "LogOnTerminal: [%s]\n"
    "Language.....: [%s]\n",
    gstGlobalPrm.szLogDir,
    gstGlobalPrm.szDebugLevel,
    gstGlobalPrm.bLogOnTerminal ? "true" : "false",
    gstGlobalPrm.szLanguage
  );

  return 0;
}

