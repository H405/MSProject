//*****************************************************************************
//	�����_���[ [CRenderer.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CRenderer.h"
#include "CDebug.h"

//*****************************************************************************
//	�ÓI�ϐ���`
//*****************************************************************************
#ifdef SCREENSHOT_ON
CScreenShot* CRenderer::screenShot;	//	�X�N���[���V���b�g�p�I�u�W�F�N�g
#endif

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	direct3D = NULL;
	device = NULL;
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
	CObj::ReleaseAll();
	SAFE_DELETE(screenShot);
	SAFE_RELEASE(device);
	SAFE_RELEASE(direct3D);
}
//=============================================================================
//	�����������֐�
//=============================================================================
void CRenderer::Init(HWND _windowHandle, BOOL _windowMode)
{
	D3DPRESENT_PARAMETERS presentParameter;
	D3DDISPLAYMODE displayMode;
	HRESULT result;

	//	Direct3D�I�u�W�F�N�g�̍쐬
	direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	if (direct3D == nullptr)
	{
		ASSERT("direct3D��nullptr�ł�")
	}

	//	���݂̃f�B�X�v���C���[�h���擾
	result = direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
	if (result == E_FAIL)
	{
		ASSERT("�f�B�X�v���C���[�h�̎擾���s")
	}

	//	�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	//--------------------------------------------------------------------
		//	���[�N���[���N���A
		ZeroMemory(&presentParameter, sizeof(presentParameter));

		//	�o�b�N�o�b�t�@�̐����Z�b�g
		presentParameter.BackBufferCount = 1;
	
		//�Q�[����ʃT�C�Y
		presentParameter.BackBufferWidth = static_cast<int>SCREEN_WIDTH;
		presentParameter.BackBufferHeight = static_cast<int>SCREEN_HEIGHT;

		//	�o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
		presentParameter.BackBufferFormat = displayMode.Format;

		//	�f���M���ɓ������ăt���b�v����
		presentParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;

		//	�E�B���h�E���[�h
		presentParameter.Windowed = _windowMode;

		//	�f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
		presentParameter.EnableAutoDepthStencil = TRUE;

		//	�f�v�X�o�b�t�@�̗��p���@
		//	D3DFMT_D16		�f�v�X�o�b�t�@�݂̂�16bit�Ƃ��Ĉ���
		//	D3DFMT_D24S8	�f�v�X�o�b�t�@��24bit�@�X�e���V���o�b�t�@��8bit�Ƃ��Ĉ���
		presentParameter.AutoDepthStencilFormat = D3DFMT_D24S8;
	//--------------------------------------------------------------------

	if (_windowMode)
	{
		//	�E�B���h�E���[�h
		presentParameter.FullScreen_RefreshRateInHz = 0;
		presentParameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		//	�t���X�N���[�����[�h
		presentParameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		presentParameter.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	//	�f�o�C�X�I�u�W�F�N�g�̐���
	//	[�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	result =
		direct3D->CreateDevice(D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								_windowHandle,
								D3DCREATE_HARDWARE_VERTEXPROCESSING,
								&presentParameter,
								&device);
	if (result == E_FAIL)
	{
		ASSERT("�f�o�C�X�̍쐬���s")
	}

	//	�����_�[�X�e�[�g�p�����[�^�̐ݒ�
	//--------------------------------------------------------------------
	//	�J�����O���[�h
	//	D3DCULL_CCW		���ʂ��J�����O(���_�̂Ȃ�����	�t���v���)
	//	D3DCULL_CW		�\�ʂ��J�����O(���_�̂Ȃ�����	���v���)
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//	Z�o�b�t�@���g�p���邩���Ȃ���
	device->SetRenderState(D3DRS_ZENABLE, TRUE);

	//	���u�����h���s�����s��Ȃ���
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//	���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//	���f�X�e�B�l�[�V�����J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//	���C�e�B���OON/OFF
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	//	���C���[�t���[���\�����邩���Ȃ���
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//--------------------------------------------------------------------

	//	�T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	//--------------------------------------------------------------------
	//	�e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	//	�J��Ԃ��ɐݒ�
	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//	�e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	//	�J��Ԃ��ɐݒ�
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//	�e�N�X�`���k���t�B���^���[�h��ݒ�
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//	�e�N�X�`���g��t�B���^���[�h��ݒ�
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//--------------------------------------------------------------------

	//	�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//--------------------------------------------------------------------
	//	�A���t�@�u�����f�B���O����
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//	�ŏ��̃A���t�@����
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	//	�Q�Ԗڂ̃A���t�@����
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//--------------------------------------------------------------------


#ifdef SCREENSHOT_ON
	screenShot = new CScreenShot(device, _windowMode, _windowHandle);
#endif

	/*obj2D = CObj2D::Create(device,
		D3DXVECTOR3(75.0f, 75.0f, 0.0f),
		3,
		D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	obj2D->setTexture("data/texture/bullete.png");

	obj2DLoop = CObj2DLoop::Create(device,
		0.0f,
		-0.1f,
		5,
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		3);
	obj2DLoop->setTexture(CTextures::TEXTURE_TEST);

	obj2DKeyFrame = CObj2DKeyFrame::Create(device,
		8,
		5,
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		3,
		D3DXVECTOR3(150.0f, 250.0f, 0.0f));
	obj2DKeyFrame->setTexture("data/texture/explosion.png");*/
}
//=============================================================================
//	�X�V����
//=============================================================================
void CRenderer::Update()
{
	CObj::UpdateAll();
}
//=============================================================================
//	�`�揈��
//	�J��������(3D)
//=============================================================================
void CRenderer::Draw(CCamera* pCamera)
{
	//	�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	device->Clear(0,
				NULL,
				(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
				D3DCOLOR_RGBA(0, 0, 0, 0),
				1.0f,
				0);

	//	Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(device->BeginScene()))
	{
		CObj::DrawAll();

#ifdef SCREENSHOT_ON
		//	�X�N���[���V���b�g�쐬
		if (screenShotFlag == true)
		{
			screenShot->Create();

			screenShotFlag = false;
		}
#endif

#ifdef _DEBUG
		CDebug::Draw();
#endif

		//	Direct3D�ɂ��`��̏I��
		device->EndScene();
	}

	//	�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ���
	device->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//	�`�揈��
//	�J��������(2D)
//=============================================================================
void CRenderer::Draw()
{
	//	�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	device->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//	Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(device->BeginScene()))
	{
		CObj::DrawAll();

#ifdef SCREENSHOT_ON
		//	�X�N���[���V���b�g�쐬
		if (screenShotFlag == true)
		{
			screenShot->Create();

			screenShotFlag = false;
		}
#endif

#ifdef _DEBUG
		CDebug::Draw();
#endif

		//	Direct3D�ɂ��`��̏I��
		device->EndScene();
	}

	//	�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ���
	device->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//	�f�o�C�X�̎擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return device;
}

//-----------------------------------EOF---------------------------------------