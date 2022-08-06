% ELE407 - Preliminary Work 5
% Egemen Can Ayduğan - 21728036

function [w] = bart(M)

M = floor(M+1); 
if M == 1  
    w = 1;     
    return
end
w = linspace(0,2,M).';    
w(w > 1) = 2-w(w > 1); 

end