#ifndef EVENDOR_H
#define EVENDOR_H

#include "epatrolbuilding.h"

class eAgoraBase;

class eVendor : public eEmployingBuilding {
public:
    using eBaseTex = std::shared_ptr<eTexture> eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    using eCharGenerator =  std::function<stdsptr<eCharacter>()>;
    eVendor(eGameBoard& board,
            const eResourceType resType,
            const eProvide provType,
            const eBaseTex& baseTex,
            const double overlayX,
            const double overlayY,
            const eBaseTex& overlayTex,
            const double overlayX2,
            const double overlayY2,
            const eOverlays& overlayTex2,
            const eBuildingType type,
            const int sw, const int sh,
            const int maxEmployees);
    ~eVendor();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    int add(const eResourceType type, const int count) override;
    int take(const eResourceType type, const int count) override;

    int count(const eResourceType type) const override;
    int spaceLeft(const eResourceType type) const override;

    std::vector<eCartTask> cartTasks() const override;

    void setAgora(const stdsptr<eAgoraBase>& agora);
    eAgoraBase* agora() const { return mAgora.get(); }

    int agoraSpaceId() const;

    eResourceType resourceType() const { return mResType; }
    eProvide provideType() const { return mProvType; }

    int peddlerResource() const;
    int takeForPeddler(const int t);

    void setResMult(const int m) { mResMult = m; }
    void setMaxRes(const int m) { mMaxResource = m; }

    bool vendorEnabled() const { return mVendorEnabled; }
    void setVendorEnabled(const bool e) { mVendorEnabled = e; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    int mResMult = 100;
    stdsptr<eAgoraBase> mAgora;
    int mMaxResource = 10*mResMult;
    const eResourceType mResType;
    const eProvide mProvType;
    const eBaseTex mBaseTex;
    const double mOverlayX;
    const double mOverlayY;
    const eBaseTex mOverlayTex;
    const double mOverlayX2;
    const double mOverlayY2;
    const eOverlays mOverlayTex2;

    stdsptr<eCharacter> mVendor;

    bool mVendorEnabled = true;

    int mResource{0};

    stdsptr<eCartTransporter> mCart;
};

#endif // EVENDOR_H
