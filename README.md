# Image Process Project and Tool Set
---
## Paint
### 1.Environment configuration
> 1. Windows 7(above)
> 2. Visual Studio 2013

### 2.Compile Code

### 3.Run
> 1. Course Requirements Location:
> > Menu:位图 --> (Rotation -- Relievo)
![](https://raw.githubusercontent.com/BasicCoder/DigitImageProcess/master/1-1403012036251U.jpg)

---
## Delur
### 1.Environment configuration
> 1. Python 2.7
> 2. Caffe
> 3. Ubuntu 14.04.5 LTS

### 2.Run
> 1. On Real Model: 
> `sh run_real_model.sh`
> 2. On Train Model: 
> `sh run_train_model.sh`

---
## ExtractSpecialFile
### 1.Environment configuration
> 1. python 3

### 2.Code:
> 1. 2017qianyi:Source Database
> 2. CollectData:Select Result

### 3.Run
> `python ExtractSpecialFile.py`

## ImageSuperResolution
### 1.Environment configuration
> 1. python 2

### 2.Code:
> 1. sh inference_SRGAN.sh

## VideoSuperResolution
### 1.Use ImageSuperResolution to process per image in Video
### 2.Merge all processed image to video.
> `python mergeImage2Video.py`

**Note:**
   > - The picture has nothing to do with the content！

![](https://raw.githubusercontent.com/BasicCoder/DigitImageProcess/master/698363.png)
