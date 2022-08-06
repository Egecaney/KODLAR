function [y] = MidriseQuantizer(x,B)
X_AbsoluteMax = max(abs(x));      
Delta = (2*X_AbsoluteMax)/(2^(B)) ;  
LevelQuantization = (2^(B-1));                      
for i=1 : length(x)
    imp(i) = abs(floor(x(i)/Delta));
    if imp(i)< LevelQuantization
        y(i) = (floor(x(i)/Delta) + 0.5)*Delta;
    elseif x(i)>0
        y(i) = (LevelQuantization-0.5)*Delta;
    elseif x(i)<0
        y(i) = (-LevelQuantization+0.5)*Delta;
    elseif x(i) == 0
        y(i) = 0;
    end
end
end