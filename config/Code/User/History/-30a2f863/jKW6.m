
% See the input files for a description
massNom         = GetNSFElement(NominalMissionNSFStr,'massNom','value');
rMarsNom        = GetNSFElement(NominalMissionNSFStr,'rMarsNom','value');
SrefNom         = GetNSFElement(NominalMissionNSFStr,'SrefNom','value');
LrefNom         = GetNSFElement(NominalMissionNSFStr,'LrefNom','value');
khfNom          = GetNSFElement(NominalMissionNSFStr,'khfNom','value');
omgMarsNom      = GetNSFElement(NominalMissionNSFStr,'omgMarsNom','value');
MmaxNom         = GetNSFElement(NominalMissionNSFStr,'MmaxNom','value');
JNom            = GetNSFElement(NominalMissionNSFStr,'JNom','value');

aMax            = MmaxNom/JNom;
parNom          = [massNom,rMarsNom,SrefNom,omgMarsNom]';

tBr1Nom         = GetNSFElement(NominalMissionNSFStr,'tBr1Nom','value');
tBr2Nom         = GetNSFElement(NominalMissionNSFStr,'tBr2Nom','value');
tBr3Nom         = GetNSFElement(NominalMissionNSFStr,'tBr3Nom','value');
tBr4Nom         = GetNSFElement(NominalMissionNSFStr,'tBr4Nom','value');
tBr5Nom         = GetNSFElement(NominalMissionNSFStr,'tBr5Nom','value');
tBr6Nom         = GetNSFElement(NominalMissionNSFStr,'tBr6Nom','value');
tBr7Nom         = GetNSFElement(NominalMissionNSFStr,'tBr7Nom','value');
tBr8Nom         = GetNSFElement(NominalMissionNSFStr,'tBr8Nom','value');

tBrVNomOrg      = [tBr1Nom,tBr2Nom,tBr3Nom,tBr4Nom,tBr5Nom,tBr6Nom,tBr7Nom,tBr8Nom];

tPDPNom         = GetNSFElement(NominalMissionNSFStr,'tPDPNom','value');
ugNom           = GetNSFElement(NominalMissionNSFStr,'ugNom','value');

TNom            = GetNSFElement(TimeStepsNSFStr,'Tgui','value');

NbrOrg          = length(tBrVNomOrg);
NbrNom          = sum(tBrVNomOrg < tPDPNom);

tBrVNom         = tBrVNomOrg(1:NbrNom);

const int x = 5;

int vettore[x]

N_Nom           = tPDPNom/TNom + 1;
uNom            = ugNom*ones(N_Nom,1);

% Build nominal bank angle profile
tSimNom         = linspace(0,tPDPNom,N_Nom)';
muNomNBR        = acos(uNom);
[muNom tBrInitNom tBrEndNom dirBrNom brFlagNom] = AddMultipleBankReversals(tSimNom,muNomNBR,tBrVNom,aMax);

xCoMNomEIP      = [ GetNSFElement(CoMNomX0NSFStr,'r0Nom','value')
    GetNSFElement(CoMNomX0NSFStr,'lon0Nom','value')
    GetNSFElement(CoMNomX0NSFStr,'lat0Nom','value')
    GetNSFElement(CoMNomX0NSFStr,'vAbs0Nom','value')
    GetNSFElement(CoMNomX0NSFStr,'fpa0Nom','value')
    GetNSFElement(CoMNomX0NSFStr,'head0Nom','value') ];

posNom_EIP_RM   = RmCoord(xCoMNomEIP(1),xCoMNomEIP(2),xCoMNomEIP(3));
xRLLNom         = xCoMNomEIP(1:3)';


%% Run Nominal Simulation

stop = false;
first = true;

idx=1;

while stop == false
    
    x0          = xCoMNomEIP;
    t1          = tPDPNom;
    Tsim        = GetNSFElement(TimeStepsNSFStr,'Tgui','value');
    
    muSim       = muNom;
    tSim        = tSimNom;
    
    disp('Nominal EIP coordinate')
    disp('----------------')
    disp(['Lon  : ' num2str(xCoMNomEIP(2)*RAD2DEG) ' deg']);
    disp(['Lat  : ' num2str(xCoMNomEIP(3)*RAD2DEG) ' deg']);
    
    
    % clc
    disp('Nom Sim...')
    sim('Sim3DOFDetailed');
    
    % Save results
    tSimNom     = tSim;
    muSimNom    = muOut;
    xCoMNom     = xOut;
    
    %% Nominal Simulation postprocessing
    % the signals computed here are useful for analysis and comparions with the
    % SimEDL output
    cDNomProf   = DLOut(:,1);
    cLNomProf   = DLOut(:,2);
    rhoNomProf  = inVarOut(:,1);
    FDNom       = inVarOut(:,2);
    FLNom       = inVarOut(:,3);
    FaWASNom    = [-FDNom,zeros(length(FDNom),1),-FLNom];
    xCoMDotNom  = xDotOut;
    machNom     = machOut;
    gNEDNom     = gNEDOut;
    
    LFNom       = sqrt(FDNom.^2 + FLNom.^2)/(massNom*9.81);
    
    rnhf        = LrefNom/4;
    qNom        = 0.5*rhoNomProf.*xCoMNom(:,4).^2;
    hfNom       = khfNom*sqrt(rhoNomProf./rnhf).*xCoMNom(:,4).^3;
    
    hAreoidNom  = zeros(length(tSimNom),1);
    hSurfNom    = zeros(length(tSimNom),1);
    
    cDMeanOnQ   = 0;
    cLMeanOnQ   = 0;
    qNorm       = sum(qNom);
    
    gravMean    = mean(gNEDNom(:,3));
    
    % This is done to compute the nominal altitude above surface over the
    % actual trajectory (latitude and longitude) of the nominal simulation
    for iii = 1:length(tSimNom)
        [patm,rho,Tmol,wEW,wNS,meanvar,extvar,seedout] = ATM_EMCD435(   xCoMNom(iii,1), ...
            1, ...
            xCoMNom(iii,2), ...
            xCoMNom(iii,3), ...
            dateLkUp, ...
            scenaLkUp, ...
            typperLkUp, ...
            invarLkUp, ...
            init_atmLkUp, ...
            ikeyLkUp, ...
            hireskeyLkUp, ...
            dsetLkUp );
        
        hAreoidNom(iii)     = extvar(2);
        hSurfNom(iii)       = extvar(3);
        
        cDMeanOnQ           = cDMeanOnQ + qNom(iii)/qNorm*cDNomProf(iii);
        cLMeanOnQ           = cLMeanOnQ + qNom(iii)/qNorm*cLNomProf(iii);
    end
    
    %% The target PDP is chosen as the final state of the nominal simulation
    xCoMPDP     = xOut(end,:);
    machNomPDP  = machNom(end);
    
    %% M. Carpentiero - 17/11/2022
    % Section added to compute the best PDP starting from the knowledge of
    % the landing site (Oxia Planum) and the maximum distance error (3 Km) admitted to perform a
    % successfull devert manouvre and pin-point landing
    
    
    PDP.R = xCoMPDP(1);
    PDP.lon = rad2deg(xCoMPDP(2));
    PDP.lat = rad2deg(xCoMPDP(3));
    
    disp(' ')
    disp('Nominal PDP State')
    disp('----------------')
    disp(['tPDP : ' num2str(tPDPNom) ' s']);
    disp(['Alt  : ' num2str(hAreoidNom(end)/1e3) ' km']);
    disp(['Lon  : ' num2str(PDP.lon) ' deg']);
    disp(['Lat  : ' num2str(PDP.lat) ' deg']);
    disp(['vAbs : ' num2str(xCoMPDP(4)) ' m/s']);
    disp(['fpa  : ' num2str(xCoMPDP(5)*RAD2DEG) ' deg']);
    disp(['head : ' num2str(xCoMPDP(6)*RAD2DEG) ' deg']);
    disp(['Mach : ' num2str(machNomPDP) ' ']);
    
    %Compute distance from landing site LS (Oxia)
    
    deg2Km = (2*pi*rMarsNom/1e3)/360;
    err_max = 10; % max error along track and cross track
    
    err.AT = (oxia_target.lon - PDP.lon)*deg2Km;
    err.CT = (oxia_target.lat - PDP.lat)*deg2Km;
    
    fprintf('Error along track (Km) = %f \n', err.AT);
    fprintf('Error cross track (Km) = %f \n', err.CT);
    fprintf('Distance from LS  (Km) = %f \n\n', norm([err.AT err.CT]));
%     
%     
%     figure(1)
%     hold all
%     title('lon vs lat')
%     plot(oxia_target.lon,oxia_target.lat,'k.','MarkerSize',15)
%     plot(xCoMNom(:,2)*180/pi,xCoMNom(:,3)*180/pi)
%     axis equal

    % stop condition: the PDP-LS error must be less than err_max (AT,CT) and
    % the PDP altitude must be in range [5-10] Km (EXM heritage)
    
    out = [xCoMNomEIP(1)/1e3 rad2deg(xCoMNomEIP(2:3))' PDP.R PDP.lon PDP.lat hAreoidNom(end)/1e3 hSurfNom(end)/1e3]; 
    
%     if abs(norm([err.AT err.CT]))<err_max && hAreoidNom(end)/1e3>5 && hAreoidNom(end)/1e3< 10.5 && first==true
        
        first = false;
        stop = true;
        save('Nominal_Trajectory.mat', 'xCoMNom','muNom','tSimNom','out');
    
%     else        
%         disp('change x0');
%         xCoMNomEIP(2) = xCoMNomEIP(2)+sign(err.AT)*deg2rad(0.025);
%         xCoMNomEIP(3) = xCoMNomEIP(3)+sign(err.CT)*deg2rad(0.0015);
%     end
    
    disp(['# Iter: ' num2str(idx)]);
    idx = idx+1;
end