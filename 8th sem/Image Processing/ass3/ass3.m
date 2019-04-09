clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = dynamic_range_changer(img, 50, 129);
figure('Name','Dynamic'),imshow(new_img);
