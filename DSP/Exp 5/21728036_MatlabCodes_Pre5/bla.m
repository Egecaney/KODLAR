% ELE407 - Preliminary Work 5
% Egemen Can Ayduðan - 21728036

function [w] = bla(M)

M = floor(M);       
N1 = ceil((M+1)/2); 
N2 = floor((M+1)/2);
n = [0:N1-1 N2-1:-1:0].';  
w = 0.42 - 0.5*(cos((2*pi*n)/(M)))+0.08*cos((4*pi*n)/(M));

end