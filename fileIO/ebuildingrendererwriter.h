#ifndef EBUILDINGRENDERERWRITER_H
#define EBUILDINGRENDERERWRITER_H

#include "buildings/ebuildingrenderer.h"
#include "fileIO/ewritestream.h"

namespace eBuildingRendererWriter {
    void sWrite(const eBuildingRenderer* const b,
                eWriteStream& dst);
};

#endif // EBUILDINGRENDERERWRITER_H
