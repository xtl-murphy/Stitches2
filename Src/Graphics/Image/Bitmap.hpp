
/**
 * Bitmap
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/6/13 1:02
 **/
#pragma once

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include "Stitches.hpp"
#include "Math/Vector2.hpp"


NS_STITCHES_BEGIN


class Bitmap : public Ref
{
public:
    Bitmap() = default;
    explicit Bitmap(std::filesystem::path filename);
    explicit Bitmap(const Vector2ui &size, uint32_t bytesPerPixel = 4);
    Bitmap(std::unique_ptr<uint8_t[]> &&data, const Vector2ui &size, uint32_t bytesPerPixel = 4);
    ~Bitmap() = default;

    void Load(const std::filesystem::path &filename);
    void Write(const std::filesystem::path &filename) const;

    explicit operator bool() const noexcept { return !data; }

    uint32_t GetLength() const;

    const std::filesystem::path &GetFilename() const { return filename; }
    void SetFilename(const std::filesystem::path &filename) { this->filename = filename; }

    const std::unique_ptr<uint8_t[]> &GetData() const { return data; }
    std::unique_ptr<uint8_t[]> &GetData() { return data; }
    void SetData(std::unique_ptr<uint8_t[]> &&data) { this->data = std::move(data); }

    const Vector2ui &GetSize() const { return size; }
    void SetSize(const Vector2ui &size) { this->size = size; }

    uint32_t GetBytesPerPixel() const { return bytesPerPixel; }
    void SetBytesPerPixel(uint32_t bytesPerPixel) { this->bytesPerPixel = bytesPerPixel; }

private:
    static uint32_t CalculateLength(const Vector2ui &size, uint32_t bytesPerPixel);

    std::filesystem::path filename;
    std::unique_ptr<uint8_t[]> data;
    Vector2ui size;
    uint32_t bytesPerPixel = 0;
};

NS_STITCHES_END