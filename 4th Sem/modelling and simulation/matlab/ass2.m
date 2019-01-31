clear;
clc;
%random network
iterations = 100

Net = [0 1 0 1; 
       1 0 1 0; 
       0 1 0 1; 
       1 0 1 0]
  
for i=1:iterations
   
   [~,numofnodes] = size(Net);
   % 0 => edge, 1 => node
  
       b=round(rand(1,numofnodes));
       Net=[[Net;b] [b 0]'];
end;
Net
hist(sum(Net));