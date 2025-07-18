from PIL import Image, ImageSequence
import numpy as np
import os
import sys

def process_single_image(img: Image.Image, base_name: str, output_prefix: str, frame_index: int = None):
    target_w, target_h = 64, 64

    # 缩放并裁剪（以中心为准，保持宽高比，目标尺寸为 64x64）
    src_w, src_h = img.size
    scale = max(target_w / src_w, target_h / src_h)
    new_w, new_h = int(src_w * scale), int(src_h * scale)
    img = img.resize((new_w, new_h), Image.LANCZOS)

    # 居中裁剪
    left = (new_w - target_w) // 2
    upper = (new_h - target_h) // 2
    right = left + target_w
    lower = upper + target_h
    img = img.crop((left, upper, right, lower))

    # 转为黑白图（二值化）
    img_bw = img.convert('L').point(lambda p: 255 if p > 128 else 0, '1')

    # 垂直翻转（上下翻转）
    img_bw = img_bw.transpose(Image.FLIP_TOP_BOTTOM)

    # 保存处理后图像
    suffix = f'_frame{frame_index}' if frame_index is not None else ''
    
    # 获取当前脚本所在目录
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # 创建输出文件夹（如果不存在）
    output_dir = os.path.join(script_dir, 'output')
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
        
    # 生成输出文件的完整路径
    out_image_name = os.path.join(output_dir, f'{output_prefix}_{base_name}{suffix}_bw.png')
    img_bw.save(out_image_name)
    print(f'保存处理图像: {out_image_name}')

    # 转换为 OLED C 数组（每页8行，每列1字节）- 阳码格式
    img_data = np.array(img_bw).astype(np.uint8)
    
    c_array = []
    for page in range(0, target_h, 8):
        for x in range(target_w):
            byte = 0
            for bit in range(8):
                if page + bit < target_h:  # 确保不越界
                    pixel = img_data[page + bit][x]
                    if pixel > 0:  # 阳码：白色像素为1（PIL的'1'模式中白色是1）
                        byte |= (1 << bit)
            c_array.append(byte)

    # 保存为 C 文件
    array_name = f'{base_name}{suffix}_image'
    
    # 使用之前创建的输出目录
    script_dir = os.path.dirname(os.path.abspath(__file__))
    output_dir = os.path.join(script_dir, 'output')
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
        
    c_file_name = os.path.join(output_dir, f'{output_prefix}_{base_name}{suffix}.c')
    with open(c_file_name, 'w') as f:
        f.write(f'// 来自: {base_name}{suffix}, OLED 64x64 图像数组 (阳码格式)\n')
        f.write(f'const uint8_t {array_name}[512] = {{\n')
        for i in range(0, 512, 16):
            line = ', '.join(f'0x{b:02X}' for b in c_array[i:i+16])
            f.write(f'    {line},\n')
        f.write('};\n')

    print(f'导出 C 数组文件: {c_file_name}')
    return out_image_name, c_file_name


def convert_image_file(filename, output_prefix='oled_output'):
    # 获取当前脚本所在目录的绝对路径
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # 将输入文件路径转换为相对于脚本目录的绝对路径
    abs_filename = os.path.join(script_dir, filename)
    
    base_name = os.path.splitext(os.path.basename(filename))[0]
    ext = os.path.splitext(filename)[1].lower()

    print(f'处理图像文件: {abs_filename}')
    
    try:
        img = Image.open(abs_filename)
        
        if ext == '.gif':
            print(f'[GIF] 正在处理 GIF: {filename}')
            for i, frame in enumerate(ImageSequence.Iterator(img)):
                frame = frame.convert('RGBA')
                process_single_image(frame, base_name, output_prefix, frame_index=i)
        else:
            print(f'[PNG] 正在处理 PNG: {filename}')
            process_single_image(img, base_name, output_prefix)
    except FileNotFoundError:
        print(f'错误：找不到文件 "{abs_filename}"')
        print(f'当前工作目录: {os.getcwd()}')
        print(f'脚本目录: {script_dir}')


# 使用示例
if __name__ == "__main__":
    # 相对路径示例，这里假设图片在与脚本同一目录
    convert_image_file("惊吓.png")
    
    # 也可以处理子文件夹中的图像
    # convert_image_file("images/test.png")
    
    # 批量处理目录中所有支持的图像文件
    # def process_all_images_in_directory(directory='images'):
    #     script_dir = os.path.dirname(os.path.abspath(__file__))
    #     img_dir = os.path.join(script_dir, directory)
    #     if os.path.exists(img_dir):
    #         for file in os.listdir(img_dir):
    #             if file.lower().endswith(('.png', '.jpg', '.jpeg', '.gif')):
    #                 print(f"\n处理文件: {file}")
    #                 convert_image_file(os.path.join(directory, file))
    #     else:
    #         print(f"目录不存在: {img_dir}")
    # 
    # process_all_images_in_directory()
