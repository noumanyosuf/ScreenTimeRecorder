# ScreenTimeRecorder
<h3> About Screen Time Recorder </h3>
Screen time recorder is a Qt and C++ based application which monitors the way you use your application, browser, presenting everything how long you've spent on certain app categories and specific apps. User has to register the applications and/or site names which they intend to be monitored. The collected data can be viewed on the viewer, representing the data in a pie chart and in tabular format.

To register a new application or site to monitor, add new entry in the screentimeanalyser.json file of the the application/site names you intent to monitor and restart the recording from ScreenTimeViewer.exe.

<h3> Introduction to windows services</h3>
In Windows operating systems, a Windows service is a computer program that operates in the background. It is similar in concept to a Unix daemon. A Windows service must conform to the interface rules and protocols of the Service Control Manager, the component responsible for managing Windows services. It is the Services and Controller app, services.exe, that launches all the services and manages their actions, such as start, end, etc

At a minimum a service requires the following items:
- A Main Entry point (like any application)
- A Service Entry point
- A Service Control Handler

For further information on window service, please go to https://docs.microsoft.com/en-us/dotnet/framework/windows-services/introduction-to-windows-service-applications
and https://skycoder42.github.io/QtService/ for github page of qtservice, a qt warpper for windows service control management.

</br>
<h3> High level design </h3>
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/HLD.PNG" width="500px"</img> 
</div>

A service is created to monitor the active window and to recorded registered windows. The data is recorded to a json file  periodically every 5 seconds and could be visualized by screentime viewer. The user can also start, stop, pause or resume the windows service from the viewer. The record timeout not yet configurable but could be easy managed in future changes to the application. 

<h3> Low level design </h3>
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/ScreenTimeRecorder.PNG" width="600px"</img> 
</div>
</br>
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/ScreenTimeService.PNG" width="400px"</img> 
</div>
</br>
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/ScreenTimeViewer.PNG" width="400px"</img> 
</div>


<h3> Application screenshots </h3>

Data visualization
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/ScreenTime_Graph.PNG" width="400px"</img> 
</div>

Windows service
<div align="center">
    <img src="https://github.com/noumanyosuf/ScreenTimeRecorder/blob/main/ScreenTime_service.png" width="400px"</img> 
</div>




  
