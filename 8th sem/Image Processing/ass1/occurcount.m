function [max_occur,min_occur] = occurcount(img)

img = double(img(:));
[a,b]=hist(img,unique(img));
[max_val,max_idx] = max(a);
[min_val,min_idx] = min(a);
max_occur = b(max_idx);
min_occur = b(min_idx);
end