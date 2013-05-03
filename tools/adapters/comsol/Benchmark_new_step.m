% Solve problem

% this is just an example that we can pass one parameter from the code 
% in the COMSOL script. The parameter which should be passed is the time step size

% this is the time step specified 
interval_length = return_timestep();
step = interval_length/1;
a = 0;
b = interval_length;

% Save current fem structure for restart purposes
fem0 = fem;
fem0.sol = fem.sol;

%ONLY FOR DEGUG PURPOSE
interval_length = return_itnumber();

% -------- CALL THE SOLVER --------
fem.sol=femtime(fem, ...
    'init',fem0.sol, ...
    'solcomp',{'u','v'}, ...
    'outcomp',{'u','v'}, ...
    'tlist',[ a : step : b ], ...
    'atol',{'0.0000010'}, ...
    'rtol',0.00001, ...
    'tout','tlist', ...
    'maxorder',1, ...    
    'initialstep',0.00002, ...
    'maxstep',0.0002);    
    
%ONLY FOR DEGUG PURPOSE
interval_length = return_itnumber();