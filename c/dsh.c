#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<curses.h>
#define BUFFERSIZE 256
char buffer[BUFFERSIZE];

//int is_fileexist(char *comm);
int  pipe1();
int redirect();
int  input_cmd();
int main()
{
  char *path,lc_char=0,*input,*arg[15];
  int li_inputlen=0,i,j,k,is_bj=0,is_back=0;
  int pid,status;
  FILE *pf; 
      pf=fopen("/home/hpc/dzh/.dshistory","a");
  while(1)
    {
     nextwhile: lc_char=0;
      input=0;
      li_inputlen=0;
      is_bj=0;
      is_back=0;
	li_inputlen=input_cmd();
      if(li_inputlen>BUFFERSIZE)
	{
	  printf("your command line is too long\n");
	  li_inputlen=0;
	  continue;
	}
      else
	{
	  buffer[li_inputlen++]=' ';
	buffer[li_inputlen]='\0';
	}
      input=(char *)malloc(sizeof(char)*(li_inputlen+1));
      strcpy(input,buffer);
      fprintf(pf,"%s\n",input);
     fflush(pf);
      //     printf("buffer:%s,%d\n",input,li_inputlen);
      //888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
       for(i=0,j=0,k=0;i<=li_inputlen;i++)
	{
	  if(input[i]=='<'||input[i]=='>'||input[i]=='|')
	    {
	     if(input[i]=='|')
	       	pipe1(input,li_inputlen);
	     //rintf("ok |");
	      else
		redirect(input,li_inputlen);
		is_bj=1;
		goto nextwhile;//break;
	    }
	  if(input[i]==' '||input[i]=='\t'||input=='\0')
	    {
	      if(j==0) 
		continue;
	      else
		{
		  buffer[j++]='\0';
		  //	  printf("%s\n",buffer);
		  arg[k]=(char*)malloc(sizeof(char)*j);
		    strcpy(arg[k],buffer);
		  j=0;
		  k++;
		}
	    }
	  else{
	  if(input[i]=='&'&&input[i+1]=='\0')
	    {
	      is_back=1;
	      continue;
	    }
	  buffer[j++]=input[i];
	  }
	}//edn for(ijk)
      free(input);
      
//       printf("arg[0]:%s\n",arg[0]);    
 //888888888888888888888888888888888888888888888888888888888888888888888888888888888888
      if(strcmp(arg[0],"ls")==0)
	{
	  
	  arg[k]=(char *)malloc(sizeof(char)*7);
	  strcpy(arg[k],"--color");
	  k++;
	}
      if(strcmp(arg[0],"exit")==0)
	{
	  printf("Thanks for using dsh\n");
	/* free(buffer);
         for(i=0;i<k;i++)
	 free(arg[i]);	 */
	  break;
	}
       else
        if(strcmp(arg[0],"cd")==0)
	  {
	    //printf("%s\n",arg[1]);
	    chdir(arg[1]);
	    continue;
	    }/*
      switch(arg[0])
	{
	case "exit":
	  printf("Thanks for using dsh\n");exit(0);
	case "cd":
	  chdir(arg[1]);
	  continue;
	  }*/
      if(is_bj==0)
	{
	  arg[k]=(char*)0;
	  if(is_fileexist(arg[0])==-1)
	    {
	      printf("command is not found!\n");
	      for(i=0;i<k;i++)
		free(arg[i]);
	      continue;
	    }
	    
         }
      //   printf("%d\n",k);
       if((pid=fork())==0)
	execv(buffer,arg);
      else
	if(is_back==0)
	waitpid(pid,&status,0);
       for(i=0;i<k;i++)
	 free(arg[i]);
    } //while(1)     
	 fclose(pf);
}//end main()
int is_fileexist(char *comm)
{
  char *path,*p;
  int i;
  i=0;
  path=getenv("PATH");
  strcat(path,"./:");
  p=path;
  while(*p!='\0')
    {
      if(*p!=':')
	buffer[i++]=*p;
      else
	{
	  buffer[i++]='/';
	  buffer[i]='\0';
	  strcat(buffer,comm);
	  if(access(buffer,F_OK)==0)
	    {
	      //  printf("%s\n",buffer);
	     return 0;
	    }
	  else
	    i=0;
	}
      p++;
    }
  return -1;
}
int redirect(char *in,int len)
{
  char *argv[30],*filename[2];
  pid_t pid;
  int i,j,k,fd_in,fd_out,is_in=-1,is_out=-1,num=0;
  int is_back=0,status=0;
  for(i=0,j=0,k=0;i<=len;i++)
    {
      if(in[i]==' '||in[i]=='\t'||in[i]=='\0'||in[i]=='<'||in[i]=='>')
	{
	  if(in[i]=='>'||in[i]=='>')
	    {
	      if(num<3)
		{
		  num++;
		  if(in[i]=='<')
		    is_in=num-1;
		  else
		    is_out=num-1;
		  if(j>0 && num==1)
		    {
		      buffer[j++]='\0';
		      argv[k]=(char *)malloc(sizeof(char)*j);
		      strcpy(argv[k],buffer);
		      k++;
		      j=0;
		      printf("num is 1");
		    }
		}
	      else
		{
		  printf("The format is error!\n");
		  return -1;
		}
	    }
	  if(j==0)
	    continue;
	  else
	    {
	      buffer[j++]='\0';
	      if(num==0)
		{
		  argv[k]=(char *)malloc(sizeof(char)*j);
		  strcpy(argv[k],buffer);
		  k++;
		}
	      else
		{
		  filename[status]=(char*)malloc(sizeof(char)*j);
		  strcpy(filename[status++],buffer);
		  printf("%s",buffer);
		}
	      j=0;
	    }
	}
      else
	{
	  if(in[i]=='&' && in[i+1]=='\0')
	    {
	      is_back=1;
	      continue;
	    }
	
	  buffer[j++]=in[i];
	}
    }
  argv[k]=(char*)0;
  if(is_fileexist(argv[0])==-1)
    {
      printf("This command is not found\n");
      for(i=0;i<k;i++)
	free(argv[i]);
      return 0;
    }
  if((pid=fork())==0)
    {
      if(is_out!=-1)
	{
	  if((fd_out=open(filename[is_out],O_WRONLY|O_CREAT|O_TRUNC,0644/*S_INUSR|S_IWUSR*/))==-1)
		  //	if((fd_out=open(filename[is_out],6,0644))==-1)
	  {
	    printf("open out %s error\n",filename[is_out]);
	    return -1;
	  }
		printf("creat ok");
	}
      if(is_in!=-1)	
	if((fd_in=open(filename[is_in],O_RDONLY,3))==-1)
	      {
		printf("open in %s error\n",filename[is_in]);
		return -1;
	      }	
      if(is_out !=-1)
	if(dup2(fd_out,STDOUT_FILENO)==-1)
	  {
	    printf("redirct standard out error\n");
	    exit(1);
	  }
      if(is_in !=-1)
	if(dup2(fd_in,STDIN_FILENO)==-1)
	  {
	    printf("redirect standard out error\n");
	    exit(1);
	  }
      execv(buffer,argv);
    }
  else
    if (is_back==0)
      waitpid(pid,&status,0);
  for(i=0;i<k;i++)
    free(argv[i]);
  if(is_in!=-1)
    {
      free(filename[is_in]);
      close(fd_in);
    }
  if(is_out!=-1)
    {
      free(filename[is_out]);
      close(fd_out);
    }
  return 0;    
}
int pipe1(char*input,int len)
{
  char *argv[2][30];
  int i,j,k,count,is_back=0,li_comm=0,fd[2],fpip[2];
  char lc_char,lc_end[1];
  pid_t child1,child2;
  for(i=0,j=0,k=0;i<=len;i++)
    {
      if(input[i]==' '||input[i]=='\t'||input[i]=='\0'||input[i]=='|')
	{
	  if(input[i]=='|')
	    {
	      if(j>0)
		{
		  buffer[j++]='\0';
		  argv[li_comm][k]=(char *)malloc(sizeof(char)*j);
		  strcpy(argv[li_comm][k++],buffer);
		}
	      argv[li_comm][k]=(char*)0;
	      li_comm++;
	      count=k;
	      //printf("%d \n",count);
	      k=0;j=0;
	    }
	  if(j==0)
	    continue;
	  else
	    {
	      buffer[j++]='\0';
	      argv[li_comm][k]=(char *)malloc(sizeof(char)*j);
	      strcpy(argv[li_comm][k],buffer);
	      k++;
	    }
	  j=0;
	}
      else
	{
	  if(input[i]=='&' &&input[i+1]=='\0')
	      {
		is_back=1;
		continue;
	      }
	     buffer[j++]=input[i];
	}
    }
      argv[li_comm][k]=(char *)0;
      //         printf("%s,%s\n%d,%d\n",argv[0][0],argv[1][0],count,k);
      if(is_fileexist(argv[0][0])==-1)
	{
	  printf("First command is not found\n");
	  for(i=0;i<count;i++)
	    free(argv[0][i]);
	  return 0;    
	}
      if(pipe(fd)==-1)
	{
	  printf("open pipe error\n");
	  return -1;
	}
      if((child1=fork())==0)
	{
	  close(fd[0]);
	  if(fd[1]!=STDOUT_FILENO)
	    {
	       if(dup2(fd[1],STDOUT_FILENO)==-1)
		{
		  printf("redirect standard out error\n");
		  return -1;
		}
	      close(fd[1]);
	    }
	  execv(buffer,argv[0]);
	}
      else
	{
	  waitpid(child1,&li_comm,0);
	  lc_end[0]=0x1a;
	  write(fd[1],lc_end,1);
	  close(fd[1]);
	  if(is_fileexist(argv[1][0])==-1)
	    {
	      printf("command is not found\n");
	      for(i=0;i<k;i++)
		free(argv[1][i]);
	      return 0;
	    }
	  if((child2=fork())==0)
	    {
	      if(fd[0]!=STDIN_FILENO)
		{
		  if(dup2(fd[0],STDIN_FILENO)==-1)
		  {
		    printf("redirect standard in error\n");
		    return -1;
		    }
		  close(fd[0]);
		     
		}
	      execv(buffer,argv[1]);
	    }
	  else
	    {
	      if(is_back==0)
		waitpid(child2,NULL,0);
	    }
	}
      for(i=0;i<k;i++)
		free(argv[0][i]);
      for(i=0;i<k;i++)
		free(argv[1][i]);
      return 0;
}
int  input_cmd()
{
	char *path;
	char in_char;
	int in_inputlen=0;
	path=(char*)get_current_dir_name();
nextenter:  printf("[%s]dzh>$",path);
      in_char=getchar();
	while(in_char==32)
		in_char=getchar();
      if(in_char=='\n') {goto nextenter;};
      while(in_char !='\n'&&in_inputlen<BUFFERSIZE)
        {
          /*if(in_char==32 )//&& in_inputlen==0)
          {
		printf("first space");
          }
	 else*/
	switch(in_char)
	{
	case 0xe0:
		printf("ctrL");
		break;
	case KEY_UP:
		printf("kdkdkdkdkdkdkkd\n");
	break;
	default:
	//	printf("%c",in_char);
		
	}
          {
                buffer[in_inputlen++]=in_char;
          }
          in_char=getc();
        }
	buffer[in_inputlen]=0;
	return in_inputlen;
}

