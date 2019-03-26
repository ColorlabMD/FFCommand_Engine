## FFCommand Engine for easier use of FFmpeg binaries.

Preloaded with preset commands from  [amiaopensource /ffmprovisr](https://github.com/amiaopensource/ffmprovisr)

This is the initial version of the software for public release.

Version v0.5 available for Mac and pc in release tab.

The windows version may requires msvc 2017 redistributable if it is not already installed. 

It is available here: [https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)

### **What it does:**

**Constructs, stores, and operates based off of FFmpeg commands.**

**Breaks down FFmpeg commands into a more easily understandable form.**

**Allows those with limited terminal experience use FFmpeg easily.**

**Creates a queue of FFmpeg processes.**

**Allows for batch processing of files without scripting knowledge.**

**Makes it easy to modify commands found online to adapt to your specific needs.**

### **What it doesn’t do:**

**Create GUI for FFmpeg**

**It provides no syntax checking**




**How to use**

1. Download FFmpeg binaries

2. Start FFCommand_Engine

3. Set FFmpeg binaries location. File-&gt;Set FFmpeg Dir ( mac uses default /usr/local/bin most users will not need to change)

4. Load a preset or copy and paste a command using the parse command button.

5. Change input and output file.

6. Add to queue.

7. Start queue.

**Batch Mode**

1. Add multiple input files.

2. Check “Batch Mode” checkbox

3. Set Ouput Directory

4. Set output file name appending

5. Add to queue

6. Start queue
