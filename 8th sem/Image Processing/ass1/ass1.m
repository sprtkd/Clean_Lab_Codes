clc;
img=load('image/l256.dat');
img=uint8(img);
[row,col,channels]=size(img)
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = thresholder(img,170);
figure('Name','thresh by 170'),imshow(new_img);
waitforbuttonpress;

max_i = max(img(:))
min_i = min(img(:))
avg = (max_i + min_i)/2
new_img = thresholder(img,avg);
figure('Name','thresh by avg'),imshow(new_img);
waitforbuttonpress;

[max_occur,min_occur] = occurcount(img)

new_img = thresholder(img,max_occur);
figure('Name','thresh by max occurence'),imshow(new_img);
waitforbuttonpress;

new_img = thresholder(img,min_occur);
figure('Name','thresh by min occurence'),imshow(new_img);
waitforbuttonpress;