models/ammo/rocket/rockflar
{
	cull disable
	{
		map models/ammo/rocket/rockflar.tga
		blendfunc GL_ONE GL_ONE
	}
}

models/ammo/rocket/rockfls2
{
	cull disable
	{
		map models/ammo/rocket/rockfls2.tga
		blendfunc GL_ONE GL_ONE
	}
}

models/ammo/grenade
{
    {
        map textures/effects/envmap_slate.tga
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen entity
        alphaGen entity
        tcGen environment
        depthWrite
    }
    {
        map models/weapons2/grenade/grenade_yd.tga
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen entity
        alphaGen entity
        depthWrite
    }
}