clock_t startTime, endTime;
startTime = clock();
//------------------------------------------------
endTime = clock();  //计时结束
printf("The running time is: %.4fs",
       (double)(endTime - startTime) / CLOCKS_PER_SEC);