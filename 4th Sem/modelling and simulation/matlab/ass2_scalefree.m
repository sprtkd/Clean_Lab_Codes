clear;
clc;
%scalefree network
iterations = 200

Net = [0 1 0 1; 
       1 0 1 0; 
       0 1 0 1; 
       1 0 1 0]
  
for i=1:iterations
   %decide if edge or node is to be added, 0 mean edge is added
   [~,numofnodes] = size(Net);  
    edgeOrNode = round(rand(1));
    if(edgeOrNode==0)
      
      %check if network has max edges
      edgeSum=sum(sum(Net));
     if(edgeSum >= ((numofnodes*numofnodes) - numofnodes))
        continue;
     end;
      %edge is added
      while(1)
      n1=round(random('unif',1,numofnodes));
      n2=round(random('unif',1,numofnodes));
      
      if((n1~=n2))
          break;
      end;
      end;
      
      Net(n1,n2)=1;
      Net(n2,n1)=1;
    else
        %node is added
       b=zeros(1,numofnodes);
       Net=[[Net;b] [b 0]'];
       NumofEdges=round(random('unif',1,numofnodes));
        if(NumofEdges==0)
			NumofEdges=1;%nodes cannot come without one edge
        end;
        for k=1:NumofEdges
            
            %find out fulldegree sum
            fullDegreeSum=sum(sum(Net));
            %add edge acc to degree sum
            edgeAddSum = round(random('unif',1,fullDegreeSum));
            fullDegreeSum = 0;
            degSumArr=sum(Net);
            for j=1:numofnodes
                
                fullDegreeSum = fullDegreeSum + degSumArr(j);
                if(edgeAddSum>=fullDegreeSum)
                    break;
                end;
                 
            end;
   
            Net(j,numofnodes+1)=1;
            Net(numofnodes+1,j)=1;
            
        end;
    end;
    
end;
Net
[~,numofnodes] = size(Net); 
numofnodes
hist(sum(Net));