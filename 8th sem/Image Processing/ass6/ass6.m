clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

dark_img = dynamic_range_changer(img,0,50);
figure('Name','dark'),imshow(dark_img);
waitforbuttonpress;

new_img = power_low_transform(dark_img,1,1.5);
figure('Name','dark_processed'),imshow(new_img);
waitforbuttonpress;

light_img = dynamic_range_changer(img,150,255);
figure('Name','light'),imshow(light_img);
waitforbuttonpress;

new_img = power_low_transform(light_img,3.6,0.72);
figure('Name','light_processed'),imshow(new_img);
waitforbuttonpress;