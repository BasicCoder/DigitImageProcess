cat fileListToProcess.txt | python processWholeImage.py --model_def ./BMVC_nets/S14_19_200.deploy --pretrained_model ./BMVC_nets/S14_19_FQ_178000.model --output_path ./out/ --tile_resolution 300 --suffix _out.png --gpu --use_mean