clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

histogram = img_hist(img);
waitforbuttonpress;
new_img = hist_eq(img,histogram);
imshow(new_img);
waitforbuttonpress;
img_hist(new_img);
waitforbuttonpress;

dark_img = dynamic_range_changer(img,0,50);
figure('Name','dark'),imshow(dark_img);
waitforbuttonpress;
histogram = img_hist(dark_img);
waitforbuttonpress;
new_img = hist_eq(dark_img,histogram);
imshow(new_img);
waitforbuttonpress;
img_hist(new_img);
waitforbuttonpress;


bright_img = dynamic_range_changer(img,200,250);
figure('Name','bright'),imshow(bright_img);
waitforbuttonpress;
histogram = img_hist(bright_img);
waitforbuttonpress;
new_img = hist_eq(bright_img,histogram);
imshow(new_img);
waitforbuttonpress;
img_hist(new_img);
waitforbuttonpress;

lowcontrast_img = dynamic_range_changer(img,50,150);
figure('Name','low contrast'),imshow(lowcontrast_img);
waitforbuttonpress;
histogram = img_hist(lowcontrast_img);
waitforbuttonpress;
new_img = hist_eq(lowcontrast_img,histogram);
imshow(new_img);
waitforbuttonpress;
img_hist(new_img);
waitforbuttonpress;

highcontrast_img = dynamic_range_changer(img,0,255);
figure('Name','high contrast'),imshow(highcontrast_img);
waitforbuttonpress;
histogram = img_hist(highcontrast_img);
waitforbuttonpress;
new_img = hist_eq(highcontrast_img,histogram);
imshow(new_img);
waitforbuttonpress;
img_hist(new_img);
waitforbuttonpress;