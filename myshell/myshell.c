#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#define COMMAND_SIZE 1024
#define FORMAT "[%s@%s %s]#"
#define MAX 128
char* g_argv[MAX];
int g_argc;
const char* GetUserName()
{
	const char* name=getenv("USER");
	return name==NULL ? "None" : name;
}
 char* GetHostName()
{
	static char buff[256];
	gethostname(buff,sizeof(buff));
	return buff;
}

const char* GetPwd()
{
	const char* pwd=getenv("PWD");
	return pwd ==NULL ? "None" : pwd;
}

void MakeCommandLine(char cmd_prompt[],int size)
{
	snprintf(cmd_prompt,size,FORMAT,GetUserName(),GetHostName(),GetPwd());
}

void PrintCmmandPrompt()
{
	char prompt[COMMAND_SIZE];
	MakeCommandLine(prompt,sizeof(prompt));
	printf("%s",prompt);
	fflush(stdout);
}

bool GetCommandLine(char* out, int size)
{
	char* c = fgets(out,size,stdin);
	if(c==NULL)
		return false;
	out[strlen(out)-1]=0;
	if(strlen(out)==0)
		return false;
	return true;

}

bool CommandParse(char* commandline)
{
#define SEP " "
	g_argc=0;
	g_argv[g_argc++]= strtok(commandline,SEP);
	while((g_argv[g_argc++] = strtok(NULL,SEP)))
	{}
		g_argc--;
	return true;
}

void PrintArgv()
{
	printf("total = %d\n",g_argc);
	for(int i=0;g_argv[i];i++)
	{
		printf("argv[%d]->%s\n",i,g_argv[i]);
	}
}

int Execute()
{
	pid_t id =fork();
	if(id==0)
	{
		//child
		execvp(g_argv[0],g_argv);
		_exit(1);
	}
	waitpid(id,NULL,0);
}
int main()
{
	while(true)
	{
		//1.输出命令行提示符
		PrintCmmandPrompt();
	
		//2.获取用户输入的命令
		char commandline[COMMAND_SIZE];
		if(GetCommandLine(commandline,sizeof(commandline))==false)
		{
			continue;
		}
		//printf("%s\n",commandline);
		//3.命令行分析 "ls -a -l" -> "ls" "-a" "-l"
		CommandParse(commandline);
		//PrintArgv();
		//4.执行命令
			Execute();

		//printf("[%s@%s %s]#",GetUserName(),GetHostName(),GetPwd());
		//fflush(stdout);
	}
	return 0;
}
