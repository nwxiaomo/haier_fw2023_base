#ifndef __DEBUG__H__
#define __DEBUG__H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "includes.h"
#include "n32g43x_Platform.h"

#if defined( __CC_ARM ) 
/* Back Ground COLOR */
#define BG_C_RED                        "\x1B[1;31m"
#define BG_C_BLUE                       "\x1B[1;34m"

/* Special function COLOR */
#define SPEC_FUNC_C_RESET                "\x1B[4;40m"  

#else
/* Back Ground COLOR */
#define BG_C_RED                        "\e[1;31m"
#define BG_C_BLUE                       "\e[1;34m"

/* Special function COLOR */
#define SPEC_FUNC_C_RESET                "\e[0m"  


#endif

#ifdef LOG
#undef LOG
#endif
#ifdef WARNING
#undef WARNING
#endif
#ifdef ERROR
#undef ERROR
#endif

/**  debug public switch **/
#ifndef LOG_OPEN
#define ASSERT_DEBUG WARNING	

#ifndef LOG
#define LOG( ... )
#endif
					  
#ifndef WARNING
#define WARNING( ... )
#endif
							  
#ifndef ERROR
#define ERROR( __FMT__ , ... )   do{ printf(" Current Error Occur -> [%s:%d] -> " __FMT__,  __FUNCTION__, __LINE__, ##__VA_ARGS__ ); }while(0)
#endif
									  
#else
#define ASSERT_DEBUG ERROR
#define CORE_NAME	platform_get_core_name()

#define LOG( __FMT__ , ... ) \
do{ \
      platform_log(LOG_DEBUG, "[%s:%d] -> "__FMT__"\n\r", __FUNCTION__, __LINE__, ##__VA_ARGS__ );\
}while(0)

#define WARNING( __FMT__ , ... ) \
do{ \
  	platform_log(LOG_WARN, BG_C_BLUE "[%s:%d] -> "__FMT__ SPEC_FUNC_C_RESET"\n\r",  __FUNCTION__, __LINE__, ##__VA_ARGS__ ); \
}while(0)

						  
//#define ERROR( __FMT__ , ... ) \
//do{ \
//	platform_log(LOG_ERROR, BG_C_RED "[%s:%d] -> "__FMT__ SPEC_FUNC_C_RESET"\n\r",  __FUNCTION__, __LINE__, ##__VA_ARGS__ ); \
//	while(1);\
//}while(0)

#define ERROR( __FMT__ , ... ) \
do{ \
	platform_log(LOG_ERROR, BG_C_RED "[%s:%d] -> "__FMT__ SPEC_FUNC_C_RESET"\n\r",  __FUNCTION__, __LINE__, ##__VA_ARGS__ ); \
}while(0)

#if 0
#define  HEX_DUMP_LOG( DATA, DATA_LEN ) \
do {\
  uint16_t col_count = 0 ; \
  char *TEMP_DATA_BUF  = (char *)MALLOC( DATA_LEN*3 + ((DATA_LEN+9)/10)*2 + 1 + 1), *TEMP_DATA_T = TEMP_DATA_BUF ; \
  uint16_t TEMP_DATA_LEN =  DATA_LEN;   \
  char *TEMP_DATA = (char*)DATA; \
  if( TEMP_DATA_T != NULL ){\
      TEMP_DATA_T += sprintf( TEMP_DATA_T, "\r\n" );\
      while( TEMP_DATA_LEN-- ){ \
        TEMP_DATA_T += sprintf( TEMP_DATA_T, "%02X ", *TEMP_DATA++ ); \
        if( ++col_count % 10 == 0 ){ TEMP_DATA_T += sprintf( TEMP_DATA_T, "\r\n" );}\
      }\
      LOG( "%s", TEMP_DATA_BUF );\
      FREE( TEMP_DATA_BUF );\
   }\
} while(0)
#endif
#endif

#define ASSERT_NULL( __Ptr__ )       do{ if( (__Ptr__) == NULL){ ASSERT_DEBUG( "  ASSERT error !!   %s is NULL", (#__Ptr__)); } }while(0)
#define ASSERT_TRUE( __Bool__ )      do{ if( !(__Bool__) ){ ASSERT_DEBUG( "  ASSERT error !!   %s is false", (#__Bool__)); } }while(0)
#define ASSERT_FALSE( __Bool__ )     do{ if( (__Bool__) ){ ASSERT_DEBUG( "  ASSERT error !!   %s is true", (#__Bool__) ); } }while(0)

#define SC_ASSERT(c, ret...) do { \
	if (!(c)) { \
		WARNING("  xxx Assert fail:%s", #c); \
		return ret; \
	} \
} while(0)


/**
  \brief   Get index usage status, In array
  \details Calculate whether the subscript of ordinary array is out of bounds
*/
#define ASSERT_OVERSTEP( __INDEX__, __INDEX_MAX__ )     do{ if((__INDEX__) >= (__INDEX_MAX__)){ ASSERT_DEBUG( "  ASSERT error !! array is out of bounds ,CUR:%d, MAX:%d", (__INDEX__) , (__INDEX_MAX__) ); } }while(0)

/**
  \brief   jude equal
  \details Judge whether the two parameters are equal
*/
#define ASSERT_EQUAL( __PARAM__, __PARAN__ )     do{ if((__PARAM__) != (__PARAN__)){ ASSERT_DEBUG( "  ASSERT error !!  %s[%d] != %s[%d]", (#__PARAM__), (__PARAM__), (#__PARAN__), (__PARAN__) ); } }while(0)

#endif

