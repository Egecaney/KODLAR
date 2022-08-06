function y = downxx(x,M)

%[x,fs]=wavread('S2_1');
%t_x=linspace(0,length(x),length(x)/M);
y=[];
for i=1:M:length(x)

    temp=x(i);
    y=[y 0 temp];    
% temp=x(i);
% y(i)=temp;
% 
% temp=x(M*i-1);
% y(i)=temp;
% y(M*i-1)=x(M*i-1);
% y(M*i)=0;
end

figure;
stem(y);

end