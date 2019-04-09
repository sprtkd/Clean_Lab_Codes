clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

noisy_img = imnoise(img);
figure('Name','Noisy'),imshow(noisy_img);
waitforbuttonpress;

new_img = kmeansfilter(noisy_img,5,15);
figure('Name','kmeans'),imshow(new_img);

mse = findmse(new_img,img)
psnr = 10*(log((255*255/mse))/log(10))