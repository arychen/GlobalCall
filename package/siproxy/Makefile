#
# Copyright (C) 2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=siproxy
PKG_VERSION:=0.9
PKG_RELEASE=$(PKG_SOURCE_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/Siproxy
	SECTION:=Siproxy
	CATEGORY:=Siproxy
	DEPENDS:=+libpthread +librt
	TITLE:=Sip client to modem communication
endef

define Package/Siproxy/description
	Sip client to modem communication
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) -r src/. $(PKG_BUILD_DIR)
endef

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)" CC="$(TARGET_CROSS)"gcc
endef

define Package/Siproxy/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/siproxy $(1)/bin/
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/paho-c/build/output/libpaho-mqtt3a.so.1 $(1)/lib/
endef

$(eval $(call BuildPackage,Siproxy))
