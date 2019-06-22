int main(){
  char *arglist[3];
  
  arglist[0] = "ls";
  arglist[1] = "-1";
  arglist[3] = 0;

  printf("* * * About to exec ls -l\n");
	execvp( "ls" , arglist );
	printf("* * * ls is done. bye\n");

  return 0;
}
