clc;
img=load('image/l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = downsampler(img);
figure('Name','Down 1'),imshow(new_img);
waitforbuttonpress;

new_img = downsampler(new_img);
figure('Name','Down 2'),imshow(new_img);
waitforbuttonpress;

new_img = upsampler(img);
figure('Name','Up 1 copying'),imshow(new_img);
new_img = upsampler(new_img);
figure('Name','Up 2 copying'),imshow(new_img);