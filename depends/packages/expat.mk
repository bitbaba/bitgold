package=expat
$(package)_version=2.2.1
$(package)_download_path=https://codeload.github.com/libexpat/libexpat/tar.gz
$(package)_download_file=R_2_1_1
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=4b829bf8a8970fdb38211bce4e60a9d47082b11d2bec94d4561ab6eabb498459

define $(package)_set_vars
$(package)_config_opts=--disable-static
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef
