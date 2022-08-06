% Egemen Can AYDUĞAN 21728036
% Preliminary Work 2 - Question 2

function [y] = inout(b,a,x,L)

for i=1:L
    numerator = 0;
    denominator = 0;
    
    for j=1:length(b)
        if (i-j+1)>0
            if (i-j+1)<length(x)
                numerator = numerator+(b(j)*x(i-j+1));
            end
        end
    end
    for j=2:length(a)
        if (i-j+1)>0
           denominator = denominator+(a(j)*y(i-j+1));
        end
    end
    
    y(i) = (numerator - denominator)/a(1);
end
end