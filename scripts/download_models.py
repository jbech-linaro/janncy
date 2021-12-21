#!/usr/bin/env python3

import torch
import os

def download_models() -> None:
    cmd("mkdir -p .pytorch")
    pytorch_path = Path(".pytorch")

    # available models: https://modelzoo.co/model/pretrained-modelspytorch
    models = [ "resnet18", "resnet152", "resnet50", "densenet121", "vgg11", "vgg13" ]

    for model_name in models:
        if not os.path.exists(pytorch_path / f"{model_name}.onnx"):
            print(f"Downloading {model_name} weights...")
            model = torch.hub.load("pytorch/vision:v0.10.0", model_name, pretrained=true)
            torch.onnx.export(model, torch.randn(1, 3, 224, 224), pytorch_path / f"{model_name}.onnx")
