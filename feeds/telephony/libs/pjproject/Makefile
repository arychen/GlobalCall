#
# Copyright (C) 2015 OpenWrt.org
# Copyright (C) 2015 Cesnet, z.s.p.o.
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=pjproject
PKG_VERSION:=2.4
PKG_RELEASE:=1

PKG_SOURCE:=pjproject-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://www.pjsip.org/release/$(PKG_VERSION)/
PKG_MD5SUM:=39629ca3fcedbdc7dbd8c5a707060095
PKG_INSTALL:=1
PKG_FIXUP:=autoreconf

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=COPYING
PKG_MAINTAINER:=Jiri Slachta <slachta@cesnet.cz>

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/pjproject/Default
  SECTION:=lib
  CATEGORY:=Libraries
  SUBMENU:=Telephony
  URL:=http://www.pjsip.org/
  DEPENDS:=+libuuid +libstdcpp +libpthread
endef

define Package/pjproject/install/lib
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/lib/$(2).so* $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/alsa-lib-1.0.28/ipkg-ramips_24kec/alsa-lib/usr/lib/libasound.so.2 $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/alsa-lib-1.0.28/ipkg-ramips_24kec/alsa-lib/usr/lib/libasound.so.2 $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/root-ramips/lib/librt.so.0 $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/root-ramips/lib/librt.so.0 $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/root-ramips/lib/libpthread.so.0 $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/root-ramips/lib/libpthread.so.0 $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/third_party/lib/libportaudio.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/third_party/lib/libportaudio.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia-audiodev.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia-audiodev.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia-videodev.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia-videodev.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia-codec.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia-codec.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjmedia/lib/libpjmedia.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjlib/lib/libpj.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjlib/lib/libpj.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjlib-util/lib/libpjlib-util.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjlib-util/lib/libpjlib-util.so $(1)/usr/lib/

	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsip-simple.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsip-ua.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsip.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsua.so $(PKG_INSTALL_DIR)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsip-simple.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsip-ua.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsip.so $(1)/usr/lib/
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip/lib/libpjsua.so $(1)/usr/lib/

	$(INSTALL_DIR) $(PKG_INSTALL_DIR)/usr/bin
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip-apps/bin/pjsua-mipsel-openwrt-linux-gnu $(PKG_INSTALL_DIR)/usr/bin/pjsua-mipsel-openwrt-linux-gnu
	$(INSTALL_BIN) $(BUILD_DIR)/pjproject-2.4/pjsip-apps/bin/pjsua-mipsel-openwrt-linux-gnu $(1)/usr/bin/pjsua-mipsel-openwrt-linux-gnu
endef

define PJSIPpackage
  define Package/$(1)
  $$(call Package/pjproject/Default)
    TITLE:=$(1) library
    DEPENDS+=$(3)
  endef

  define Package/$(1)/install
$(call Package/pjproject/install/lib,$$(1),$2)
  endef

  $$(eval $$(call BuildPackage,$(1)))
endef

CONFIGURE_ARGS += \
	--enable-shared \
	--disable-floating-point \
	--enable-g711-codec \
	--enable-l16-codec \
	--enable-g722-codec \
	--disable-g7221-codec \
	--disable-gsm-codec \
	--disable-ilbc-coder \
	--disable-ipp \
	--disable-ssl \
	--disable-oss \
	--enable-sound \
	--with-external-srtp="$(STAGING_DIR)/usr" \
	--without-external-gsm \
	--disable-small-filter \
	--disable-large-filter \
	--disable-speex-aec \
	--enable-g711-codec \
	--enable-l16-codec \
	--disable-gsm-codec \
	--enable-g722-codec \
	--disable-g7221-codec \
	--disable-speex-codec \
	--disable-ilbc-codec \
	--disable-resample-dll \
	--disable-sdl \
	--disable-ffmpeg \
	--disable-v4l2

#--with-silk="/home/cld/openwrt/SWT/SILK_SDK_SRC_MIPS_v1.0.9" \

TARGET_LDFLAGS+=-lc $(LIBGCC) -lm
TARGET_CFLAGS+=$(EXTRA_CFLAGS) $(TARGET_CPPFLAGS) $(EXTRA_CPPFLAGS)

define Build/Compile
	$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR)
endef

PJPROJECT_LIBS = \
	libpj libpjlib-util libpjmedia-audiodev libpjmedia-codec \
	libpjmedia-videodev libpjmedia libpjnath libpjsip-simple \
	libpjsip-ua libpjsip libpjsua libpjsua2 libresample

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/{include,lib}
	
	$(CP) -R $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/

	$(foreach m,$(PJPROJECT_LIBS),$(CP) $(PKG_INSTALL_DIR)/usr/lib/$(m)* $(1)/usr/lib/;)
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libpjproject.pc $(1)/usr/lib/pkgconfig/
endef

$(eval $(call PJSIPpackage,libpj,libpj,+librt +libresample +libsrtp +libpjmedia))
$(eval $(call PJSIPpackage,libpjlib-util,libpjlib-util,+libpj +librt +libresample +libsrtp +libpjmedia))
$(eval $(call PJSIPpackage,libpjmedia,libpjmedia*,+libpj +libpjlib-util +libpjnath +libresample +librt +libspeex +libsrtp))
$(eval $(call PJSIPpackage,libpjnath,libpjnath,+libpj +libpjlib-util +librt +libsrtp +libresample +libsrtp))
$(eval $(call PJSIPpackage,libpjsip-simple,libpjsip-simple,+libpj +libpjlib-util +libpjsip +libresample +librt +libspeex +libsrtp))
$(eval $(call PJSIPpackage,libpjsip-ua,libpjsip-ua,+libpj +libpjlib-util +libpjmedia +libpjsip-simple +libpjsip +libresample +librt +libspeex +libsrtp))
$(eval $(call PJSIPpackage,libpjsip,libpjsip,+libpj +libpjlib-util +libresample +librt +libspeex +libsrtp))
$(eval $(call PJSIPpackage,libpjsua,libpjsua,+libpj +libpjlib-util +libpjmedia +libpjnath +libpjsip-simple +libpjsip-ua +libpjsip +libresample +librt +libspeex +libsrtp))
$(eval $(call PJSIPpackage,libpjsua2,libpjsua2,+libpj +libpjlib-util +libpjmedia +libpjnath +libpjsip-simple +libpjsip-ua +libpjsip +libresample +librt +libspeex +libsrtp +libpjsua))
$(eval $(call PJSIPpackage,libresample,libresample,+libpj +libsrtp +libpjmedi +libpjlib-util +libpjnath))
