/**
 * =====================================================================================
 *       @file    testcall2.c
 *
 *       @brief   Call other function.  
 *
 *       @author  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *       @version 1.0
 *       @date    01/02/2011 06:43:04 PM
 *
 *       Revision none
 *       Compiler gcc
 *       Company  
 * =====================================================================================
 */

char hello_str[]="a string";
/**
 * @brief call function 
 *
 * @param pfn
 * @param ...
 */
__declspec(naked) void call(void* pfn, ...) 
{
#if defined(__GNUC__)
#elif defined(_MSC_VER)
#endif
    __asm 
    {                             //!stack is snapshot after executing the current line
                                  //!stack: EIP_main print_str hello_str
        pop eax;                  //!stack: print_str hello_str //!eax= EIP_main 
//        add eax, 3;               //!EIP_main +3 , why? because after call there is "add esp, 8" which should be replaced with "add esp , 4" 
        xchg dword ptr[esp], eax; //!stack: EIP_main+3 hello_str //!eax=print_str
        push eax;                 //!stack: print_str EIP_main+3 hello_str
        ret;                      //!stack: EIP_main+3 hello_str   EIP=print_str
    }
}


/**
 * @brief  
 *
 * @param s
 */
void  print_str( const char *s )
{
    printf( "%s\n", s );
}

/**
 * @brief 
 *
 * @return 
 */
int main(){
    /**
     * @name 
     * @code 
     * 012B144E  push        offset hello_str (12B7038h) 
     * 012B1453  push        offset print_str (12B11E5h) 
     * 012B1458  call        call (12B119Fh)  //! stack: 012B145D(EIP_main) print_str hello_str 
     * 012B145D  add         esp,8 
     * @{ */
                                 //! 012B144E  push        offset hello_str (12B7038h) 
                                 //! 012B1453  push        offset print_str (12B11E5h) 
    call( print_str, hello_str); //! 012B1458  call        call (12B119Fh)  //! stack: 012B145D(EIP_main) print_str hello_str 
                                 //! 012B145D  add         esp,8 
    
    __asm sub esp, 4 //!sizeof(print_str) : if print_str is cdecl, this should be executed.
    /**  @} */
}
