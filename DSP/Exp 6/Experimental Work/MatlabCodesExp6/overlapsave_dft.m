function [y]=overlapsave_dft(x,h,L)
P=length(h);
N=length(x);
x=[zeros(1,P-1) x]; % zero padding(length of P)
num_b=length(x)/(L-P); % to calculate how many blocks are there
x=[x zeros(1,5*(L-P))];
y=[];% in order to use as input below
for i=0:num_b;
temp=dft(x((L-P)*i+1:(L-P)*i+L),h,L);
y=cat(2,y,temp(P+1:end)); %combine y and dft result of new block
end
y=datawrap(y,N+P-1);
end
