% Egemen Can AYDUÐAN 21728036
% Preliminary Work 2 - Question 3

function [y] = myAR(x,a)

if length(x) == 1
    y(1) = x;
    return
end

hold = 0;
TempY = zeros(1,length(x)-1);
L = length(a);

for i=L:-1:1
    if length(x) > i
        TempY = myAR(x(1:end-i),a)
        hold = hold + (a(i)*TempY(end));
    end
end

ResultY = x(length(x))- hold;
y = [TempY,ResultY];
end


