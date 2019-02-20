function [new_img ] = hist_eq( img,hist )
[row,col,channels]=size(img);
new_img = zeros(row,col,1);
pdf = hist/(row*col);
cdf = pdf;
curr_tot = 0;
for i=1:length(pdf)
    curr_tot = curr_tot + pdf(i);
    cdf(i) = curr_tot;
end
cdf = round(cdf*255);
for i=1:row
    for j=1:col
        new_img(i,j) = cdf(img(i,j)+1);
    end
end
new_img = uint8(new_img);
end