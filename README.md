# ScreenTimeRecorder
<h3> About Screen Time Recorder </h3>
Screen time recorder is a Qt and C++ based application which monitors the way you use your application, browser, presenting everything how long you've spent on certain app categories and specific apps. User has to register the applications and/or site names which they intened to be monitored.The collected data can be viewed on the viewer, respresnting the data in a pie chart and in tabular formate.

To register a new application or site to monitor, add new entry in the screentimeanalyser.json file of the the application/site names you intent to monitor and restart the recording from ScreenTimeViewer.exe.

</br>
<h3> High level design </h3>
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/HLD.PNG" width="400px"</img> 
</div>

A windows is created to monitor the monitor of the active window and is recorded if the windows is registered by user. The entired is recorded to a json file  periodically every 5 seconds and could be visualized by screentime viewer. The user can also start, stop, pause or resume the windows service by the viewer.

<h3> Low level design </h3>
:screenshot -LLD

</br>
<h3> Screenshots </h3>

Data visualization
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/ScreenTime_Graph.PNG" width="400px"</img> 
</div>
</br>
Windows service
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/ScreenTime_service.png" width="400px"</img> 
</div>




  
