
#ifndef  cvsort_INC
#define  cvsort_INC

#define CV_SWAP(a,b,t) ((t) = (a), (a) = (b), (b) = (t)) 
#ifndef MIN
#define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

template<class T, int (*cvCMP)(const T&, const T&)>
void cvQsort( T *array, size_t total)                        
{                                                                                 
	const int isort_thresh = 7;                                                         
    T t;                                                                          
    int sp = 0;                                                                   
                                                                                  
    struct                                                                        
    {                                                                             
        T *lb;                                                                    
        T *ub;                                                                    
    }                                                                             
    stack[48];                                                                    
                                                                                  
                                                                                  
    if( total <= 1 )                                                              
        return;                                                                   
                                                                                    
    stack[0].lb = array;                                                            
    stack[0].ub = array + (total - 1);                                              
                                                                                    
    while( sp >= 0 )                                                                
    {                                                                               
        T* left = stack[sp].lb;                                                     
        T* right = stack[sp--].ub;                                                  
                                                                                    
        for(;;)                                                                     
        {                                                                           
            int i, n = (int)(right - left) + 1, m;                                  
            T* ptr;                                                                 
            T* ptr2;                                                                
                                                                                    
            if( n <= isort_thresh )                                                 
            {                                                                      
            insert_sort:                                                           
                for( ptr = left + 1; ptr <= right; ptr++ )                         
                {                                                                  
                    for( ptr2 = ptr; ptr2 > left && cvCMP(ptr2[0],ptr2[-1]); ptr2--)  
                        CV_SWAP( ptr2[0], ptr2[-1], t );                           
                }                                                                  
                break;                                                              
            }                                                                       
            else                                                                    
            {                                                                       
                T* left0;                                                           
                T* left1;                                                           
                T* right0;                                                          
                T* right1;                                                          
                T* pivot;                                                           
                T* a;                                                               
                T* b;                                                               
                T* c;                                                               
                int swap_cnt = 0;                                                   
                                                                                    
                left0 = left;                                                       
                right0 = right;                                                     
                pivot = left + (n/2);                                               
                                                                                    
                if( n > 40 )                                                        
                {                                                                   
                    int d = n / 8;                                                  
                    a = left, b = left + d, c = left + 2*d;                         
                    left = cvCMP(*a, *b) ? (cvCMP(*b, *c) ? b : (cvCMP(*a, *c) ? c : a))     
                                      : (cvCMP(*c, *b) ? b : (cvCMP(*a, *c) ? a : c));    
                                                                                    
                    a = pivot - d, b = pivot, c = pivot + d;                        
                    pivot = cvCMP(*a, *b) ? (cvCMP(*b, *c) ? b : (cvCMP(*a, *c) ? c : a))    
                                      : (cvCMP(*c, *b) ? b : (cvCMP(*a, *c) ? a : c));    
                                                                                    
                    a = right - 2*d, b = right - d, c = right;                      
                    right = cvCMP(*a, *b) ? (cvCMP(*b, *c) ? b : (cvCMP(*a, *c) ? c : a))    
                                      : (cvCMP(*c, *b) ? b : (cvCMP(*a, *c) ? a : c));    
                }                                                                   
                                                                                    
                a = left, b = pivot, c = right;                                     
                pivot = cvCMP(*a, *b) ? (cvCMP(*b, *c) ? b : (cvCMP(*a, *c) ? c : a))        
                                   : (cvCMP(*c, *b) ? b : (cvCMP(*a, *c) ? a : c));       
                if( pivot != left0 )                                                
                {                                                                   
                    CV_SWAP( *pivot, *left0, t );                                   
                    pivot = left0;                                                  
                }                                                                   
                left = left1 = left0 + 1;                                           
                right = right1 = right0;                                            
                                                                                    
                for(;;)                                                             
                {                                                                   
                    while( left <= right && !cvCMP(*pivot, *left) )                    
                    {                                                               
                        if( !cvCMP(*left, *pivot) )                                    
                        {                                                           
                            if( left > left1 )                                      
                                CV_SWAP( *left1, *left, t );                        
                            swap_cnt = 1;                                           
                            left1++;                                                
                        }                                                           
                        left++;                                                     
                    }                                                               
                                                                                    
                    while( left <= right && !cvCMP(*right, *pivot) )                   
                    {                                                               
                        if( !cvCMP(*pivot, *right) )                                   
                        {                                                           
                            if( right < right1 )                                    
                                CV_SWAP( *right1, *right, t );                      
                            swap_cnt = 1;                                           
                            right1--;                                               
                        }                                                           
                        right--;                                                    
                    }                                                               
                                                                                    
                    if( left > right )                                              
                        break;                                                      
                    CV_SWAP( *left, *right, t );                                    
                    swap_cnt = 1;                                                   
                    left++;                                                         
                    right--;                                                        
                }                                                                   
                                                                                    
                if( swap_cnt == 0 )                                                 
                {                                                                   
                    left = left0, right = right0;                                   
                    goto insert_sort;                                               
                }                                                                   
                                                                                    
                n = MIN( (int)(left1 - left0), (int)(left - left1) );               
                for( i = 0; i < n; i++ )                                            
                    CV_SWAP( left0[i], left[i-n], t );                              
                                                                                    
                n = MIN( (int)(right0 - right1), (int)(right1 - right) );           
                for( i = 0; i < n; i++ )                                            
                    CV_SWAP( left[i], right0[i-n+1], t );                           
                n = (int)(left - left1);                                            
                m = (int)(right1 - right);                                          
                if( n > 1 )                                                         
                {                                                                   
                    if( m > 1 )                                                     
                    {                                                               
                        if( n > m )                                                 
                        {                                                           
                            stack[++sp].lb = left0;                                 
                            stack[sp].ub = left0 + n - 1;                           
                            left = right0 - m + 1, right = right0;                  
                        }                                                           
                        else                                                        
                        {                                                           
                            stack[++sp].lb = right0 - m + 1;                        
                            stack[sp].ub = right0;                                  
                            left = left0, right = left0 + n - 1;                    
                        }                                                           
                    }                                                               
                    else                                                            
                        left = left0, right = left0 + n - 1;                        
                }                                                                   
                else if( m > 1 )                                                    
                    left = right0 - m + 1, right = right0;                          
                else                                                                
                    break;                                                          
            }                                                                       
        }                                                                           
    }                                                                               
}

#endif   /* ----- #ifndef cvsort_INC  ----- */
