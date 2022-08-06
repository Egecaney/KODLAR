% Egemen Can Ayduðan - 21728036
% Preliminary Work 6

function y = convfilt(x,h,N)

h = h(:).';
x = x(:).';

if (N>=length(x))&&(N>=length(h))
    h = [h zeros(1,N-length(h))];
    x = [x zeros(1,N-length(x))];   
elseif (N<length(x))&&(N>=length(h)) 
    h = [h zeros(1,N-length(h))];
    x = x(1:N);    
else
    h = h(1:N);
    x = x(1:N);    
end

h = fliplr(h);
y = zeros(1,N);

for j = 1:N
    h = wshift(1,h,-1);
    y(j) = sum(x.*h);    
end

end


    