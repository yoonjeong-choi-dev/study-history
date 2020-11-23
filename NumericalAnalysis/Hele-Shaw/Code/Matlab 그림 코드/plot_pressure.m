clear all
clc
close all


level=4;
nsR=2^level;

dx=1/2^level;
dy=1/2^level;


nFrames = 160;
vidObj = VideoWriter('Pressure_circle4.avi');
vidObj.Quality = 100;
vidObj.FrameRate = 10;
open(vidObj);


x2(2)=0;
y2(2)=0;

nIP=0;
for i=1:nFrames
    i
    
    close  all
    
    figure ('position',[100 100 600 600])
    hold on  
   
   str_1='IIM_PRESSURE';
   str_2=num2str(i);
   str_3='_';
   str_4=num2str(level);
   str_5='.m';
   str1=[str_1 str_2 str_3 str_4]; 
   run(str1);
   
   view(50,40)
   zlim([-0.1 1.1])
 
   writeVideo(vidObj, getframe);
   
end

close(vidObj);